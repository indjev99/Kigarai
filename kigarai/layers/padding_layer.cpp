#include "padding_layer.h"

inline unsigned int encodeIndex(unsigned int d, unsigned int w, unsigned int h, const Structure& s)
{
    return d*s.heigth*s.width+h*s.width+w;
}
PaddingLayer::PaddingLayer(const Structure& padding, const Structure& prevStructure, const std::vector<double>& prevValues)
    : Layer({prevStructure.depth,prevStructure.heigth+padding.heigth,prevStructure.width+padding.width},prevStructure,prevValues)
    , padding{padding} {}
PaddingLayer::~PaddingLayer() {}
void PaddingLayer::calc_values()
{
    for (unsigned int d=0;d<prevStructure.depth;++d)
    {
        for (unsigned int h=0;h<prevStructure.heigth;++h)
        {
            for (unsigned int w=0;w<prevStructure.width;++w)
            {
                unsigned int i=encodeIndex(d,h,w,prevStructure);
                unsigned int j=encodeIndex(d,h+padding.heigth/2,w+padding.width/2,structure);
                values[j]=prevValues[i];
            }
        }
    }
}
void PaddingLayer::train(const std::vector<double>& dCost0dValues, std::vector<double>& dCost0dPrevValues)
{
    for (unsigned int d=0;d<prevStructure.depth;++d)
    {
        for (unsigned int h=0;h<prevStructure.heigth;++h)
        {
            for (unsigned int w=0;w<prevStructure.width;++w)
            {
                unsigned int i=encodeIndex(d,h,w,prevStructure);
                unsigned int j=encodeIndex(d,h+padding.heigth/2,w+padding.width/2,structure);
                dCost0dPrevValues[i]=dCost0dValues[j];
            }
        }
    }
}
void PaddingLayer::apply_training(double lambda) {}
