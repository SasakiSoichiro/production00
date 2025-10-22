xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 12;
 -3.35620;3.95513;-33.43389;,
 -12.59711;38.41883;-16.82401;,
 20.83680;29.27549;-14.95210;,
 -26.31260;8.88488;-14.95210;,
 -19.54490;-41.94385;-7.59267;,
 14.41952;-21.36524;-15.54621;,
 5.88469;50.17076;10.67424;,
 -27.54921;35.78097;16.82401;,
 -28.83295;-20.04868;8.89212;,
 12.78624;-37.01405;10.48835;,
 31.69735;3.95513;9.52073;,
 -3.35620;3.95513;33.43389;;
 
 20;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,2,5;,
 3;2,1,6;,
 3;1,3,7;,
 3;3,4,8;,
 3;4,5,9;,
 3;5,2,10;,
 3;2,6,10;,
 3;1,7,6;,
 3;3,8,7;,
 3;4,9,8;,
 3;5,10,9;,
 3;10,6,11;,
 3;6,7,11;,
 3;7,8,11;,
 3;8,9,11;,
 3;9,10,11;;
 
 MeshMaterialList {
  3;
  20;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.288800;0.677600;0.429600;0.459000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.159923;0.375221;0.237891;;
  }
  Material {
   0.800000;0.800000;0.800000;0.451000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  22;
  -0.320715;-0.007020;-0.947150;,
  -0.352678;0.693674;-0.628040;,
  0.714097;0.455183;-0.531859;,
  -0.860883;0.067332;-0.504327;,
  -0.590247;-0.351182;-0.726828;,
  0.611180;-0.478765;-0.630271;,
  0.653104;-0.073920;-0.753652;,
  0.586098;0.760891;-0.278449;,
  -0.815231;0.543473;-0.200090;,
  -0.967274;-0.105800;-0.230623;,
  0.379244;-0.803371;-0.459097;,
  0.648749;-0.669529;-0.361740;,
  0.956929;-0.032916;-0.288450;,
  -0.410076;0.905240;-0.111258;,
  -0.292332;-0.651256;0.700292;,
  0.028934;-0.512680;0.858092;,
  -0.393510;-0.471427;0.789244;,
  0.563455;0.017956;0.825951;,
  0.247817;0.387687;0.887854;,
  0.427091;0.159920;0.889954;,
  -0.282376;0.266326;0.921593;,
  -0.505136;-0.293615;0.811559;;
  20;
  3;0,1,2;,
  3;0,3,1;,
  3;0,4,3;,
  3;0,5,4;,
  3;6,2,5;,
  3;2,1,7;,
  3;1,3,8;,
  3;3,4,9;,
  3;10,5,11;,
  3;5,2,12;,
  3;2,7,12;,
  3;1,8,13;,
  3;3,9,8;,
  3;14,15,16;,
  3;5,12,11;,
  3;17,18,19;,
  3;18,20,19;,
  3;20,16,21;,
  3;16,15,21;,
  3;15,17,19;;
 }
}
