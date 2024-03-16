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


    void PushLayer(const Ref<Layer>& layer);
    void PopLayer(const Ref<Layer>& layer);

    void PushOverlay(const Ref<Layer>& overlay);
    void PopOverlay(const Ref<Layer>& overlay);

    void PopAll();

    inline std::vector<Ref<Layer>>::iterator begin() { return layerPtrs.begin(); }
    inline std::vector<Ref<Layer>>::iterator end() { return layerPtrs.end(); }
    inline bool empty() { return layerPtrs.empty(); }

    // Which index do the layers get pushed to
    int currentLayerIndex = 0;
    // After which index do the layers created by the user start
    int userLayerStartIndex = 0;
    // After which index do the layers created by the user start
    int userLayerEndIndex = 0;

    // Which index do the layers get pushed to
    int currentOverlayIndex = 0;
    // After which index do the layers created by the user start
    int userOverlayStartIndex = 0;
    // After which index do the layers created by the user start
    int userOverlayEndIndex = 0;
private:
    std::vector<Ref<Layer>> layerPtrs;
};


#endif //CLOSING_LAYERSTACK_H
