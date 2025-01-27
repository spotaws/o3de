/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include "CommandSystemConfig.h"
#include <MCore/Source/Command.h>
#include <MCore/Source/CommandGroup.h>
#include <EMotionFX/Source/AnimGraph.h>


namespace CommandSystem
{
    // Adjust a group parameter.
    MCORE_DEFINECOMMAND_START(CommandAnimGraphAdjustGroupParameter, "Adjust anim graph group parameter", true)
    public:
        enum Action
        {
            ACTION_ADD,
            ACTION_REMOVE,
            ACTION_NONE
        };
        Action GetAction(const MCore::CommandLine& parameters);

        AZStd::string                   mOldName;                   //! group parameter name before command execution.
        AZStd::vector<AZStd::string>    mOldGroupParameterNames;
        bool                            mOldDirtyFlag;
        AZStd::string                   m_oldDescription;
    MCORE_DEFINECOMMAND_END

    // Add a group parameter.
    MCORE_DEFINECOMMAND_START(CommandAnimGraphAddGroupParameter, "Add anim graph group parameter", true)
        bool                mOldDirtyFlag;
        AZStd::string       mOldName;
    MCORE_DEFINECOMMAND_END

    // Remove a group parameter.
    MCORE_DEFINECOMMAND_START(CommandAnimGraphRemoveGroupParameter, "Remove anim graph group parameter", true)
        AZStd::string       mOldName;
        AZStd::string       mOldParameterNames;
        AZStd::string       mOldParent;
        size_t              mOldIndex;
        bool                mOldDirtyFlag;
    MCORE_DEFINECOMMAND_END

    // helper functions
    COMMANDSYSTEM_API void RemoveGroupParameter(EMotionFX::AnimGraph* animGraph, const EMotionFX::GroupParameter* groupParameter, bool removeParameters, MCore::CommandGroup* commandGroup = nullptr, bool updateUI = true);
    COMMANDSYSTEM_API void ClearGroupParameters(EMotionFX::AnimGraph* animGraph, MCore::CommandGroup* commandGroup = nullptr);
    COMMANDSYSTEM_API void MoveGroupParameterCommand(EMotionFX::AnimGraph* animGraph, uint32 moveFrom, uint32 moveTo);
} // namespace CommandSystem
