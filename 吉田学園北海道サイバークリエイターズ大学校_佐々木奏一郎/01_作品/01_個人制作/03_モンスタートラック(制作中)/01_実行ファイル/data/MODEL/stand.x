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
 20;
 -8.18747;0.00301;8.18747;,
 8.18747;0.00301;8.18747;,
 6.25717;2.03054;6.25717;,
 -6.25717;2.03054;6.25717;,
 5.28517;5.08220;5.28517;,
 -5.28517;5.08220;5.28517;,
 5.07808;9.17481;5.07808;,
 -5.07808;9.17481;5.07808;,
 8.41643;37.60535;8.41643;,
 -8.41643;37.60535;8.41643;,
 8.41643;37.60535;-8.41643;,
 -8.41643;37.60535;-8.41643;,
 5.07808;9.17481;-5.07808;,
 -5.07808;9.17481;-5.07808;,
 5.28517;5.08220;-5.28517;,
 -5.28517;5.08220;-5.28517;,
 6.25717;2.03054;-6.25717;,
 -6.25717;2.03054;-6.25717;,
 8.18747;0.00301;-8.18747;,
 -8.18747;0.00301;-8.18747;;
 
 18;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,1,0;,
 4;1,18,16,2;,
 4;2,16,14,4;,
 4;4,14,12,6;,
 4;6,12,10,8;,
 4;19,0,3,17;,
 4;17,3,5,15;,
 4;15,5,7,13;,
 4;13,7,9,11;;
 
 MeshMaterialList {
  2;
  18;
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
   0.401569;0.395294;0.078431;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.152234;0.149855;0.029733;;
  }
 }
 MeshNormals {
  22;
  0.000000;0.689528;0.724259;,
  0.000000;0.560054;0.828456;,
  0.000000;0.191479;0.981497;,
  0.000000;-0.034820;0.999394;,
  0.000000;-0.116620;0.993177;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.116620;-0.993177;,
  0.000000;-0.034820;-0.999394;,
  0.000000;0.191479;-0.981497;,
  0.000000;0.560054;-0.828456;,
  0.000000;0.689528;-0.724259;,
  0.000000;-1.000000;0.000000;,
  0.724259;0.689528;0.000000;,
  0.828456;0.560054;0.000000;,
  0.981497;0.191479;0.000000;,
  0.999394;-0.034820;0.000000;,
  0.993177;-0.116620;0.000000;,
  -0.724259;0.689528;0.000000;,
  -0.828456;0.560054;0.000000;,
  -0.981497;0.191479;0.000000;,
  -0.999394;-0.034820;-0.000000;,
  -0.993177;-0.116620;-0.000000;;
  18;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;5,5,5,5;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;9,9,10,10;,
  4;11,11,11,11;,
  4;12,12,13,13;,
  4;13,13,14,14;,
  4;14,14,15,15;,
  4;15,15,16,16;,
  4;17,17,18,18;,
  4;18,18,19,19;,
  4;19,19,20,20;,
  4;20,20,21,21;;
 }
}
