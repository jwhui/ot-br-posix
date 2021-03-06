/*
 *  Copyright (c) 2020, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   The file implements POSIX system utilities.
 */

#define OTBR_LOG_TAG "UTILS"

#include "system_utils.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "common/logging.hpp"

namespace otbr {
namespace SystemUtils {

enum
{
    kSystemCommandMaxLength = 1024, ///< Max length of a system call command.
};

int ExecuteCommand(const char *aFormat, ...)
{
    char    cmd[kSystemCommandMaxLength];
    int     exitCode;
    va_list args;

    va_start(args, aFormat);
    vsnprintf(cmd, sizeof(cmd), aFormat, args);
    va_end(args);

    exitCode = system(cmd);

    if (exitCode == 0)
    {
        otbrLogInfo("$?=%-3d: %s", exitCode, cmd);
    }
    else
    {
        otbrLogWarning("$?=%-3d: %s", exitCode, cmd);
    }

    return exitCode;
}

} // namespace SystemUtils
} // namespace otbr
