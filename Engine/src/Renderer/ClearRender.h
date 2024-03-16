//
// Created by Let'sBlend on 16/03/2024.
//

#ifndef CLOSINGIN_CLEARRENDER_H
#define CLOSINGIN_CLEARRENDER_H

#include "SystemsManager/Layer.h"

class ClearRender : public Layer
{
public:
    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;
};


#endif //CLOSINGIN_CLEARRENDER_H
