/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#if !defined(Q_MOC_RUN)
#include <AzCore/std/containers/array.h>
#include "../EMStudioConfig.h"
#include "RenderOptions.h"
#include "RenderWidget.h"
#include <QWidget>
#include <QMenu>
#include <QToolBar>
#include <QSettings>
#include <QHBoxLayout>
#include <QPushButton>
#include <QContextMenuEvent>
#endif


namespace EMStudio
{
    // forward declaration
    class OpenGLRenderPlugin;
    class PreferencesWindow;

    class EMSTUDIO_API RenderViewWidget
        : public QWidget
    {
        Q_OBJECT // AUTOMOC
        MCORE_MEMORYOBJECTCATEGORY(RenderViewWidget, MCore::MCORE_DEFAULT_ALIGNMENT, MEMCATEGORY_EMSTUDIOSDK_RENDERPLUGINBASE);

    public:
        RenderViewWidget(RenderPlugin* parentPlugin, QWidget* parentWidget);
        virtual ~RenderViewWidget();

        void CreateActions();

        enum ERenderFlag
        {
            RENDER_SOLID                    = 0,
            RENDER_WIREFRAME                = 1,
            RENDER_LIGHTING                 = 2,
            RENDER_TEXTURING                = 3,
            RENDER_SHADOWS                  = 4,
            RENDER_FACENORMALS              = 5,
            RENDER_VERTEXNORMALS            = 6,
            RENDER_TANGENTS                 = 7,
            RENDER_AABB                     = 8,
            RENDER_OBB                      = 9,
            RENDER_COLLISIONMESHES          = 10,
            RENDER_SKELETON                 = 11,
            RENDER_LINESKELETON             = 12,
            RENDER_NODEORIENTATION          = 13,
            RENDER_NODENAMES                = 14,
            RENDER_GRID                     = 15,
            RENDER_BACKFACECULLING          = 16,
            RENDER_ACTORBINDPOSE            = 17,
            RENDER_RAGDOLL_COLLIDERS        = 18,
            RENDER_RAGDOLL_JOINTLIMITS      = 19,
            RENDER_HITDETECTION_COLLIDERS   = 20,
            RENDER_USE_GRADIENTBACKGROUND   = 21,
            RENDER_MOTIONEXTRACTION         = 22,
            RENDER_CLOTH_COLLIDERS          = 23,
            RENDER_SIMULATEDOBJECT_COLLIDERS= 24,
            RENDER_SIMULATEJOINTS           = 25,
            NUM_RENDER_OPTIONS              = 26
        };

        MCORE_INLINE bool GetRenderFlag(ERenderFlag option)     { return mActions[(uint32)option] ? mActions[(uint32)option]->isChecked() : false; }
        void SetRenderFlag(ERenderFlag option, bool isEnabled);
        uint32 FindActionIndex(QAction* action);
        RenderWidget* GetRenderWidget() const                   { return mRenderWidget; }
        QMenu* GetCameraMenu() const                            { return mCameraMenu; }

        void SaveOptions(QSettings* settings);
        void LoadOptions(QSettings* settings);

        bool GetIsCharacterFollowModeActive() const             { return mFollowCharacterAction->isChecked(); }
        void SetCharacterFollowModeActive(bool active);

        void OnContextMenuEvent(QWidget* renderWidget, bool ctrlPressed, int32 localMouseX, int32 localMouseY, QPoint globalMousePos, RenderPlugin* plugin, MCommon::Camera* camera);

        void SetManipulatorMode(RenderOptions::ManipulatorMode mode);

    public slots:
        void OnOptions();
        void OnOrbitCamera()                                    { mRenderWidget->SwitchCamera(RenderWidget::CAMMODE_ORBIT); UpdateInterface(); }
        void OnFirstPersonCamera()                              { mRenderWidget->SwitchCamera(RenderWidget::CAMMODE_FIRSTPERSON); UpdateInterface(); }
        void OnOrthoFrontCamera()                               { mRenderWidget->SwitchCamera(RenderWidget::CAMMODE_FRONT); UpdateInterface(); }
        void OnOrthoBackCamera()                                { mRenderWidget->SwitchCamera(RenderWidget::CAMMODE_BACK); UpdateInterface(); }
        void OnOrthoLeftCamera()                                { mRenderWidget->SwitchCamera(RenderWidget::CAMMODE_LEFT); UpdateInterface(); }
        void OnOrthoRightCamera()                               { mRenderWidget->SwitchCamera(RenderWidget::CAMMODE_RIGHT); UpdateInterface(); }
        void OnOrthoTopCamera()                                 { mRenderWidget->SwitchCamera(RenderWidget::CAMMODE_TOP); UpdateInterface(); }
        void OnOrthoBottomCamera()                              { mRenderWidget->SwitchCamera(RenderWidget::CAMMODE_BOTTOM); UpdateInterface(); }
        void OnResetCamera(float flightTime = 1.0f)
        {
            MCommon::Camera* camera = mRenderWidget->GetCamera();
            if (camera)
            {
                camera->Reset(flightTime);
            }
        }
        void OnShowSelected();
        void OnShowEntireScene();
        void OnFollowCharacter();
        void OnReset()                                          { Reset(); }

        void UpdateInterface();

    private:
        void CreateViewOptionEntry(QMenu* menu, const char* menuEntryName, int32 actionIndex, bool visible = true, const char* iconFilename = nullptr);
        QAction* AddToolBarAction(const char* entryName, const char* iconName);
        void Reset();

        QToolBar*                           mToolBar;
        QMenu*                              mCameraMenu;
        RenderWidget*                       mRenderWidget;
        QAction*                            mActions[NUM_RENDER_OPTIONS];
        QAction*                            mFollowCharacterAction;
        AZStd::vector<AZStd::pair<QAction*, RenderWidget::CameraMode>> m_cameraModeActions;
        QPushButton*                        mToolbarButtons[NUM_RENDER_OPTIONS];
        AZStd::array<QAction*, RenderOptions::NUM_MODES> m_manipulatorModes;
        RenderPlugin*                       mPlugin;
        PreferencesWindow*                  mRenderOptionsWindow;
    };
} // namespace EMStudio
