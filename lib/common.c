/* Copyright (C) 2015 Jaguar Land Rover Automotive PLC.

   This file is part of Common.

   Common is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Common is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with Common.  If not, see <http://www.gnu.org/licenses/>. */

#include <config.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include "XW_Extension.h"
#include "common-api.h"
#include "common.h"

static XW_Extension extension = 0;
static const XW_CoreInterface *core = 0;
static const XW_MessagingInterface *messaging = 0;

static void instance_created(XW_Instance instance) {}

static void instance_destroyed(XW_Instance instance) {}

static void handle_message(XW_Instance instance, const char *json) {
  json_t *request, *response;
  json_error_t error;
  char *dump, *message;
  int id;

  response = json_object();
  json_object_set_new(response, "err", json_null());
  json_object_set_new(response, "id", json_null());

  request = json_loads(json, 0, &error);
  if (!request) {
    fprintf(stderr, "JSON error on line %d: %s\n", error.line, error.text);
    json_object_set_new(response, "err", json_string("JSON parsing error"));
    goto done;
  }

  json_unpack(request, "{siss}", "id", &id, "message", &message);
  json_object_set_new(response, "id", json_integer(id));

  json_object_set_new(response, "response", json_string("/foo/bar"));

 done:
  dump = json_dumps(response, JSON_INDENT(2));
  messaging->PostMessage(instance, dump);
  free(dump);
}

static void shutdown(XW_Extension ext) {}

int32_t XW_Initialize(XW_Extension ext, XW_GetInterface get_interface) {
  char kSource_common_api[common_api_js_len+1];

  memcpy(kSource_common_api, common_api_js, common_api_js_len);
  kSource_common_api[common_api_js_len] = '\0';

  extension = ext;

  core = get_interface(XW_CORE_INTERFACE);
  core->SetExtensionName(ext, PACKAGE);
  core->SetJavaScriptAPI(ext, kSource_common_api);
  core->RegisterInstanceCallbacks(ext, instance_created, instance_destroyed);
  core->RegisterShutdownCallback(ext, shutdown);

  messaging = get_interface(XW_MESSAGING_INTERFACE);
  messaging->Register(ext, handle_message);

  return XW_OK;
}

char *common_version(void) {
  return strdup(VERSION);
}
