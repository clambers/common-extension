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
#include <dlog/dlog.h>
#include "XW_Extension.h"
#include "common-api.h"
#include "common.h"

static XW_Extension extension = 0;
static const XW_CoreInterface *core = 0;
static const XW_MessagingInterface *messaging = 0;

static void instance_created(XW_Instance instance) {
  SLOGI("Creating instance");
}

static void instance_destroyed(XW_Instance instance) {
  SLOGI("Destroying instance");
}

static void handle_message(XW_Instance instance, const char *msg) {
  char *res;

  SLOGI("Received message");

  if (strcmp(msg, "get-version") == 0) {
    res = common_get_version();
  } else if (strcmp(msg, "get-path") == 0) {
    res = common_get_path();
  } else {
    res = strdup("Internal error");
    SLOGE("Internal JS error: '%s' is not a valid message", msg);
  }

  SLOGI("Posting response");

  messaging->PostMessage(instance, res);
  free(res);
}

static void shutdown(XW_Extension ext) {
  SLOGI("Shutting down");
}

int32_t XW_Initialize(XW_Extension ext, XW_GetInterface get_interface) {
  SLOGI("Initializing");

  extension = ext;

  core = get_interface(XW_CORE_INTERFACE);
  core->SetExtensionName(ext, PACKAGE);
  core->SetJavaScriptAPI(ext, kSource_common_api);
  core->RegisterInstanceCallbacks(ext, instance_created, instance_destroyed);
  core->RegisterShutdownCallback(ext, shutdown);

  messaging = get_interface(XW_MESSAGING_INTERFACE);
  messaging->Register(ext, handle_message);

  SLOGI("Initialization complete");

  return XW_OK;
}

char *common_get_version(void) {
  return strdup(PACKAGE_VERSION);
}

char *common_get_path(void) {
  return strdup(COMMON_PATH);
}
