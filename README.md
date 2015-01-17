PICCANTE
========

The hottest hdr imaging library

PICCANTE is a C++11 image processing library aimed to provide structures and functionalities for enabling both High Dynamic Range (HDR) and standard imaging.

HOW TO INSTALL:
===============

1) Unzip the file .zip in a FOLDER on your machine

2) Add piccante include directory in your include path

3) Include "piccante.hpp" in your project

TEAM:
=====

Francesco Banterle

Luca Benedetti

LICENSE:
========
Piccante is distributed under the MPL 2.0 license: https://www.mozilla.org/MPL/2.0/

SCREENSHOT:
===========
Piccante can be used for generating HDR images starting from a stack of classic 8-bit
images.

->![HDR Generation](/screenshots/hdr_generation.png?raw=true "HDR Generation")<-

Piccante can manage different color spaces, and new ones can be added to its core with easy and simple steps!

->![Color Spaces](/screenshots/color_spaces.png?raw=true "Color Spaces")<-

Piccante has provides algorithms for tone mapping HDR images in order to be visualized on traditional displays.

->![Tone Mapping](/screenshots/tone_mapping.png?raw=true "Tone Mapping")<-

Piccante can filter images using a high quality selection of linear and non linear filters.

->![Filtering](/screenshots/filtering.png?raw=true "Filtering")<-

Piccante can extract local features for different tasks such as image alignments, classification, 3D reconstruction, etc.

->![Local Features](/screenshots/local_features.png?raw=true "Local Features")<-

REFERENCE:
==========

Please reference PICCANTE in your work using this reference:

@misc{banterle:pic:2014,

 Author = {Francesco Banterle and Luca Benedetti},

 Title = {{PICCANTE: An Open and Portable Library
          for HDR Imaging}},

 Year  = {2014},

 Howpublished = {\url{http://vcg.isti.cnr.it/piccante}
 }