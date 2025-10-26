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
 24;
 -54.56771;0.17768;-24.25679;,
 -54.56771;0.17768;25.74320;,
 -54.56771;19.18498;25.74320;,
 -54.56771;19.18498;-24.25679;,
 -54.23100;27.65309;-24.25679;,
 -54.23100;27.65309;25.74320;,
 -4.90441;41.97423;25.74320;,
 -4.90442;41.97423;-24.25680;,
 54.56771;19.18498;-24.25681;,
 54.56771;19.18498;25.74319;,
 54.56771;0.17768;25.74319;,
 54.56771;0.17768;-24.25681;,
 -4.56772;0.17768;-24.25680;,
 -4.56771;0.17768;25.74320;,
 -4.56771;19.18498;25.74320;,
 -4.56772;19.18498;-24.25680;,
 -0.10056;6.09583;-20.47975;,
 -0.10056;6.09583;21.96615;,
 50.10054;6.09583;21.96614;,
 50.10054;6.09583;-20.47976;,
 -0.10056;19.18498;21.96615;,
 -0.10056;19.18498;-20.47975;,
 50.10054;19.18498;21.96614;,
 50.10054;19.18498;-20.47976;;
 
 22;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,1,0;,
 4;1,13,14,2;,
 4;12,0,3,15;,
 4;3,2,5,4;,
 4;2,14,6,5;,
 4;14,15,7,6;,
 4;15,3,4,7;,
 4;16,17,18,19;,
 4;14,13,10,9;,
 4;13,12,11,10;,
 4;12,15,8,11;,
 4;15,14,20,21;,
 4;14,9,22,20;,
 4;9,8,23,22;,
 4;8,15,21,23;,
 4;21,20,17,16;,
 4;20,22,18,17;,
 4;22,23,19,18;,
 4;23,21,16,19;;
 
 MeshMaterialList {
  1;
  22;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  27;
  -1.000000;0.000000;0.000000;,
  -0.999803;0.019869;0.000000;,
  -0.278820;0.960344;0.000000;,
  -0.278820;0.960344;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.999210;0.039731;0.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.999891;0.014773;-0.000000;,
  0.999891;0.014773;-0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;;
  22;
  4;0,0,1,1;,
  4;2,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,7,8,9;,
  4;10,11,12,13;,
  4;1,1,14,14;,
  4;9,8,15,16;,
  4;17,18,17,18;,
  4;13,12,19,19;,
  4;20,20,20,20;,
  4;8,7,21,21;,
  4;5,5,5,5;,
  4;10,13,22,22;,
  4;20,20,20,20;,
  4;20,23,20,20;,
  4;23,20,20,20;,
  4;20,20,20,20;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;0,0,0,0;,
  4;26,26,26,26;;
 }
}
