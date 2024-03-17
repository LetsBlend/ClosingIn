//
// Created by Let'sBlend on 28/02/2024.
//

#ifndef CLOSING_LAYERSTACK_H
#define CLOSING_LAYERSTACK_H

class Layer;

class LayerStack
{
public:
    LayerStack() = default;
    ~LayerStack();

    void PushUserLayer(const Ref<Layer>& layer);
    void PushEngineLayer(const Ref<Layer>& layer);
    void PopUserLayer(const Ref<Layer>& layer);
    void PopEngineLayer(const Ref<Layer>& layer);

    void PushUserOverlay(const Ref<Layer>& overlay);
    void PushEngineOverlay(const Ref<Layer>& overlay);
    void PopUserOverlay(const Ref<Layer>& overlay);
    void PopEngineOverlay(const Ref<Layer>& overlay);

    void PopAll();

    inline std::vector<Ref<Layer>>::iterator begin() { return layerPtrs.begin(); }
    inline std::vector<Ref<Layer>>::iterator end() { return layerPtrs.end(); }
    inline bool empty() { return layerPtrs.empty(); }

    // Which index do the users layers get pushed to
    int currentUserLayerIndex = 0;

    // Which index do the users overlays get pushed to
    int currentUserOverlayIndex = 0;
private:
    std::vector<Ref<Layer>> layerPtrs;
};


#endif //CLOSING_LAYERSTACK_H
