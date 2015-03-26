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
#include <string.h>
#include "common.h"

char *common_version(void) {
  return strdup(VERSION);
}
