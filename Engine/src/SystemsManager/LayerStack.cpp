//
// Created by Let'sBlend on 28/02/2024.
//

#include "LayerStack.h"
#include "Layer.h"

LayerStack::~LayerStack()
{
    PopAll();
}

void LayerStack::PushLayer(const Ref<Layer>& layer)
{
    layerPtrs.insert(layerPtrs.begin() + userLayerStartIndex + currentLayerIndex, layer);
    currentLayerIndex++;
    layer->OnAttach();
}

void LayerStack::PopLayer(const Ref<Layer>& layer)
{
    layer->OnDetach();
    auto id = std::find(layerPtrs.begin(), layerPtrs.end(), layer);

    layerPtrs.erase(id);
}

void LayerStack::PushOverlay(const Ref<Layer> &overlay)
{
    layerPtrs.insert(layerPtrs.end() + userOverlayStartIndex + currentOverlayIndex, overlay);
    currentOverlayIndex++;
    overlay->OnAttach();
}

void LayerStack::PopOverlay(const Ref<Layer> &overlay)
{
    overlay->OnDetach();
    auto id = std::find(layerPtrs.begin(), layerPtrs.end(), overlay);

    layerPtrs.erase(id);
}

void LayerStack::PopAll()
{
    for(const Ref<Layer>& layer : layerPtrs)
    {
        layer->OnDetach();
    }

    layerPtrs.clear();
}
