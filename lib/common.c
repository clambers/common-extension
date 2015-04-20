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

#define LOG_TAG PACKAGE_NAME

#include <config.h>
#include <stdlib.h>
#include <string.h>
#include <dlog/dlog.h>
#include "XW_Extension.h"
#include "XW_Extension_SyncMessage.h"
#include "common-api.h"
#include "common.h"

static XW_Extension extension = 0;
static const XW_CoreInterface *core = 0;
static const XW_MessagingInterface *async_messaging = 0;
static const XW_Internal_SyncMessagingInterface *sync_messaging = 0;

static void instance_created(XW_Instance instance) {}

static void instance_destroyed(XW_Instance instance) {}

static void handle_message(XW_Instance instance, const char *msg) {}

static void handle_sync_message(XW_Instance instance, const char *msg) {
  char *res;

  LOGI("getting common path");
  res = common_get_path();
  LOGI("common path retrieved");
  sync_messaging->SetSyncReply(instance, res);
  LOGI("common path response sent");
  free(res);
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

  async_messaging = get_interface(XW_MESSAGING_INTERFACE);
  async_messaging->Register(ext, handle_message);

  sync_messaging = get_interface(XW_INTERNAL_SYNC_MESSAGING_INTERFACE);
  sync_messaging->Register(ext, handle_sync_message);

  return XW_OK;
}

char *common_version(void) {
  return strdup(PACKAGE_VERSION);
}

char *common_get_path(void) {
  return strdup(COMMON_PATH);
}
