//
// Created by Let'sBlend on 16/03/2024.
//

#ifndef CLOSINGIN_EDITORGUI_H
#define CLOSINGIN_EDITORGUI_H

#include "SystemsManager/GuiLayer.h"

class EditorGui : public GuiLayer
{
public:
    void OnAttach() override;
    void OnDetach() override;

    void OnGui() override;
};


#endif //CLOSINGIN_EDITORGUI_H
