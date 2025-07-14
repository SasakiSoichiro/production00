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
 15;
 0.00000;6.68174;8.11533;,
 2.24302;13.58505;3.62929;,
 -5.87230;10.94822;3.62929;,
 7.25857;6.68174;3.62929;,
 2.24302;-0.22157;3.62929;,
 -5.87230;2.41526;3.62929;,
 -2.24302;13.58505;-3.62929;,
 2.24302;13.58505;3.62929;,
 7.25857;6.68174;3.62929;,
 5.87230;10.94822;-3.62929;,
 2.24302;-0.22157;3.62929;,
 5.87230;2.41526;-3.62929;,
 -2.24302;-0.22157;-3.62929;,
 -7.25857;6.68174;-3.62929;,
 0.00000;6.68174;-8.11533;;
 
 20;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,2,5;,
 3;2,1,6;,
 3;7,8,9;,
 3;8,10,11;,
 3;4,5,12;,
 3;5,2,13;,
 3;2,6,13;,
 3;7,9,6;,
 3;8,11,9;,
 3;10,12,11;,
 3;5,13,12;,
 3;13,6,14;,
 3;6,9,14;,
 3;9,11,14;,
 3;11,12,14;,
 3;12,13,14;;
 
 MeshMaterialList {
  1;
  20;
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
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  12;
  0.000000;-0.000000;1.000000;,
  -0.723607;0.525731;0.447214;,
  0.276393;0.850651;0.447214;,
  0.894427;-0.000000;0.447214;,
  0.276393;-0.850651;0.447214;,
  -0.723607;-0.525731;0.447214;,
  -0.894427;-0.000000;-0.447214;,
  -0.276393;0.850651;-0.447214;,
  0.723607;0.525731;-0.447214;,
  0.723607;-0.525731;-0.447214;,
  -0.276393;-0.850651;-0.447214;,
  -0.000000;-0.000000;-1.000000;;
  20;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,1,5;,
  3;1,2,7;,
  3;2,3,8;,
  3;3,4,9;,
  3;4,5,10;,
  3;5,1,6;,
  3;1,7,6;,
  3;2,8,7;,
  3;3,9,8;,
  3;4,10,9;,
  3;5,6,10;,
  3;6,7,11;,
  3;7,8,11;,
  3;8,9,11;,
  3;9,10,11;,
  3;10,6,11;;
 }
 MeshTextureCoords {
  15;
  1.000000;0.500000;,
  1.088104;0.823792;,
  0.838104;0.676208;,
  1.176208;0.500000;,
  1.088104;0.176208;,
  0.838104;0.323792;,
  0.588104;0.823792;,
  0.088104;0.823792;,
  0.176208;0.500000;,
  0.338104;0.676208;,
  0.088104;0.176208;,
  0.338104;0.323792;,
  0.588104;0.176208;,
  0.676208;0.500000;,
  0.500000;0.500000;;
 }
}
