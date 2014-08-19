/*

PICCANTE
The hottest HDR imaging library!
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

PICCANTE is free software; you can redistribute it and/or modify
under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 3.0 of
the License, or (at your option) any later version.

PICCANTE is distributed in the hope that it will be useful, but
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License
( http://www.gnu.org/licenses/lgpl-3.0.html ) for more details.

*/

#ifndef PIC_FILTERING_FILTER_LUMINANCE_HPP
#define PIC_FILTERING_FILTER_LUMINANCE_HPP

#include "filtering/filter.hpp"

namespace pic {

enum LUMINANCE_TYPE{LT_CIE_LUMINANCE, LT_WARD_LUMINANCE, LT_MEAN};

/**
 * @brief The FilterLuminance class
 */
class FilterLuminance: public Filter
{
protected:

    LUMINANCE_TYPE  type;
    float           *weights;
    int             weights_size;

    /**
     * @brief ProcessBBox
     * @param dst
     * @param src
     * @param box
     */
    void ProcessBBox(ImageRAW *dst, ImageRAWVec src, BBox *box)
    {
        int width    = src[0]->width;
        int channels = src[0]->channels;
        float *data  = src[0]->data;

        int transformChannels = MIN(channels, weights_size);

        for(int j = box->y0; j < box->y1; j++) {
            int c = j * width;

            for(int i = box->x0; i < box->x1; i++) {
                int indOut = c + i;
                int ind = indOut * channels;

                float sum = 0.0f;
                for(int k=0;k<transformChannels;k++)
                {
                    sum += data[ind + k] * weights[k];
                }

                dst->data[indOut] = sum;
            }
        }
    }

    /**
     * @brief SetupAux
     * @param imgIn
     * @param imgOut
     * @return
     */
    ImageRAW *SetupAux(ImageRAWVec imgIn, ImageRAW *imgOut)
    {
        if(imgOut == NULL) {
            imgOut = new ImageRAW(1, imgIn[0]->width, imgIn[0]->height, 1);
        } else {
            if((imgIn[0]->width  != imgOut->width)  ||
               (imgIn[0]->height != imgOut->height) ||
               (imgOut->channels != 1)) {
                imgOut = new ImageRAW(1, imgIn[0]->width, imgIn[0]->height, 1);
            }
        }

        if( (weights_size != imgIn[0]->channels) && (type == LT_MEAN) )
        {
            weights_size = imgIn[0]->channels;

            if(weights != NULL) {
                delete[] weights;
            }

            weights = new float [weights_size];

            for(int i=0; i<imgIn[0]->channels; i++) {
                weights[i] = 1.0f / float( imgIn[0]->channels );
            }
        }

        return imgOut;
    }

public:

    /**
     * @brief FilterLuminance
     * @param type
     */
    FilterLuminance(LUMINANCE_TYPE type = LT_CIE_LUMINANCE)
    {
        weights = NULL;
        weights_size = -1;

        Update(type);
    }

    ~FilterLuminance()
    {
        if(weights != NULL)
        {
            delete[] weights;
        }
    }

    /**
     * @brief Update
     * @param type
     */
    void Update(LUMINANCE_TYPE type = LT_CIE_LUMINANCE)
    {
        this->type = type;

        if(weights != NULL) {
            delete[] weights;
        }

        weights = NULL;

        switch(type)
        {

        case LT_WARD_LUMINANCE:
            {
                weights = new float[3];
                weights_size = 3;
                weights[0] =  54.0f  / 256.0f;
                weights[1] =  183.0f / 256.0f;
                weights[2] =  19.0f  / 256.0f;
            }
            break;

        case LT_CIE_LUMINANCE:
            {
                weights = new float[3];
                weights_size = 3;
                weights[0] =  0.213f;
                weights[1] =  0.715f;
                weights[2] =  0.072f;
            }
            break;

        case LT_MEAN:
            {
                weights = NULL;
                weights_size = -1;
            }
            break;
        }
    }

    /**
     * @brief OutputSize
     * @param imgIn
     * @param width
     * @param height
     * @param channels
     * @param frames
     */
    void OutputSize(ImageRAW *imgIn, int &width, int &height, int &channels, int &frames)
    {
        width       = imgIn->width;
        height      = imgIn->height;
        channels    = 1;
        frames      = imgIn->frames;
    }

    /**
     * @brief Execute
     * @param imgIn
     * @param imgOut
     * @param type
     * @return
     */
    static ImageRAW *Execute(ImageRAW *imgIn, ImageRAW *imgOut, LUMINANCE_TYPE type = LT_CIE_LUMINANCE)
    {
        FilterLuminance fltLum(type);
        return fltLum.ProcessP(Single(imgIn), imgOut);
    }

    /**
     * @brief Execute
     * @param fileInput
     * @param fileOutput
     * @return
     */
    static ImageRAW *Execute(std::string fileInput, std::string fileOutput)
    {
        ImageRAW imgIn(fileInput);
        ImageRAW *out = FilterLuminance::Execute(&imgIn, NULL, LT_CIE_LUMINANCE);
        out->Write(fileOutput);
        return out;
    }
};

} // end namespace pic

#endif /* PIC_FILTERING_FILTER_LUMINANCE_HPP */

