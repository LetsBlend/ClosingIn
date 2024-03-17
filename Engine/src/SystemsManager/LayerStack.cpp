//
// Created by Let'sBlend on 28/02/2024.
//

#include "LayerStack.h"
#include "Layer.h"

LayerStack::~LayerStack()
{
    PopAll();
}

void LayerStack::PushUserLayer(const Ref<Layer>& layer)
{
    layerPtrs.insert(layerPtrs.begin() + currentUserLayerIndex, layer);
    currentUserLayerIndex++;
    layer->OnAttach();
}

void LayerStack::PushEngineLayer(const Ref<Layer> &layer)
{
    layerPtrs.push_back(layer);
    layer->OnAttach();
}

void LayerStack::PopUserLayer(const Ref<Layer>& layer)
{
    layer->OnDetach();
    currentUserLayerIndex--;
    auto id = std::find(layerPtrs.begin(), layerPtrs.end(), layer);

    layerPtrs.erase(id);
}

void LayerStack::PopEngineLayer(const Ref<Layer> &layer)
{
    layer->OnDetach();
    auto id = std::find(layerPtrs.begin(), layerPtrs.end(), layer);

    layerPtrs.erase(id);
}

void LayerStack::PushUserOverlay(const Ref<Layer> &overlay)
{
    layerPtrs.insert(layerPtrs.end() + currentUserOverlayIndex, overlay);
    currentUserOverlayIndex++;
    overlay->OnAttach();
}

void LayerStack::PushEngineOverlay(const Ref<Layer> &overlay)
{
    layerPtrs.push_back(overlay);
    overlay->OnAttach();
}

void LayerStack::PopUserOverlay(const Ref<Layer> &overlay)
{
    overlay->OnDetach();
    currentUserOverlayIndex--;

    auto id = std::find(layerPtrs.begin(), layerPtrs.end(), overlay);
    layerPtrs.erase(id);
}

void LayerStack::PopEngineOverlay(const Ref<Layer> &overlay)
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
