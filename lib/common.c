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

#define LOG_TAG PACKAGE

#include <config.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dlog/dlog.h>
#include <jansson.h>
#include "XW_Extension.h"
#include "common-api.h"
#include "common.h"

static XW_Extension extension = 0;
static const XW_CoreInterface *core = 0;
static const XW_MessagingInterface *messaging = 0;

static void instance_created(XW_Instance instance) {
  SLOGI("creating instance");
}

static void instance_destroyed(XW_Instance instance) {
  SLOGI("destroying instance");
}

static void handle_message(XW_Instance instance, const char *msg) {
  json_t *root, *id, *cmd, *res, *rel;
  json_error_t err;
  const char *cmd_value, *rel_value;
  char *root_value, *res_value, *path_value;

  SLOGI("received message");

  res = json_object();

  root = json_loads(msg, 0, &err);
  if (!json_is_object(root)) {
    SLOGE("message doesn't appear to be a JSON object");
    goto done;
  }

  root_value = json_dumps(root, 0);
  SLOGI("parsed input: %s", root_value);

  id = json_object_get(root, "id");
  if (!json_is_integer(id)) {
    SLOGE("message id isn't an integer");
    goto done;
  }

  json_object_set(res, "id", id);
  json_object_set_new(res, "result", json_string("internal error"));

  cmd = json_object_get(root, "cmd");
  if (!json_is_string(cmd)) {
    SLOGE("message cmd isn't a string");
    goto done;
  }

  cmd_value = json_string_value(cmd);

  if (strcmp(cmd_value, "get-version") == 0) {
    json_object_set_new(res, "result", json_string(common_getVersion()));
  } else if (strcmp(cmd_value, "get-path") == 0) {
    rel = json_object_get(root, "rel");
    if (!json_is_string(rel)) {
      SLOGE("argument 'rel' isn't a string");
      goto done;
    }

    rel_value = json_string_value(rel);
    path_value = common_getPath(rel_value);
    json_object_set_new(res, "result", json_string(path_value));
    free(path_value);
  } else {
    SLOGE("internal JS error: invalid cmd '%s'", cmd_value);
    goto done;
  }

 done:
  json_decref(root);
  res_value = json_dumps(res, 0);
  SLOGI("posting response: %s", res_value);
  messaging->PostMessage(instance, res_value);
  json_decref(res);
}

static void shutdown(XW_Extension ext) {
  SLOGI("shutting down");
}

int32_t XW_Initialize(XW_Extension ext, XW_GetInterface get_interface) {
  SLOGI("initializing");

  extension = ext;

  core = get_interface(XW_CORE_INTERFACE);
  core->SetExtensionName(ext, PACKAGE);
  core->SetJavaScriptAPI(ext, kSource_common_api);
  core->RegisterInstanceCallbacks(ext, instance_created, instance_destroyed);
  core->RegisterShutdownCallback(ext, shutdown);

  messaging = get_interface(XW_MESSAGING_INTERFACE);
  messaging->Register(ext, handle_message);

  SLOGI("initialization complete");

  return XW_OK;
}

char *common_getVersion(void) {
  return strdup(PACKAGE_VERSION);
}

char *common_getPath(const char *rel) {
  size_t length;
  char *path;
  char invalid;

  invalid = !rel;

  length = strlen(COMMONDIR) + (invalid ? 0 : strlen(rel)) + 9;
  path = malloc(length);
  strcpy(path, "file://");
  strcat(path, COMMONDIR);
  strcat(path, "/");
  if (!invalid) {
    strcat(path, rel);
  }

  return path;
}
