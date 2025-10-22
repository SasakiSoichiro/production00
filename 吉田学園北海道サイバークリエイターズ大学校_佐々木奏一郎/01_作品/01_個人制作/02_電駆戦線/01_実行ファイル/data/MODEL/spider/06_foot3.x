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
 8;
 -0.37218;-19.37610;-0.08123;,
 0.09517;-19.37610;-0.08123;,
 1.18835;-9.23730;0.60387;,
 -1.46536;-9.23730;0.60387;,
 0.04037;0.90151;-0.08123;,
 -0.31740;0.90151;-0.08123;,
 1.18835;-9.23730;-0.76633;,
 -1.46536;-9.23730;-0.76633;;
 
 8;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,1,0;,
 3;1,6,2;,
 3;2,6,4;,
 3;0,3,7;,
 3;7,3,5;;
 
 MeshMaterialList {
  4;
  8;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.028000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.385000;0.000000;0.013475;;
  }
  Material {
   0.000000;0.006400;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.489600;0.000000;0.800000;1.000000;;
   5.000000;
   0.238000;0.238000;0.238000;;
   0.301104;0.000000;0.492000;;
  }
 }
 MeshNormals {
  19;
  0.000000;-0.067418;0.997725;,
  0.000000;-0.067418;0.997725;,
  0.000000;-0.000123;1.000000;,
  0.000000;-0.000123;1.000000;,
  0.000000;0.067418;0.997725;,
  0.000000;0.067418;0.997725;,
  0.000000;0.067418;-0.997725;,
  0.000000;0.067418;-0.997725;,
  0.000000;-0.000123;-1.000000;,
  0.000000;-0.000123;-1.000000;,
  0.000000;-0.067418;-0.997725;,
  0.994237;-0.107200;0.000000;,
  0.999996;0.002671;0.000000;,
  0.999996;0.002671;0.000000;,
  0.993651;0.112507;0.000000;,
  -0.994237;-0.107200;0.000000;,
  -0.999996;0.002671;0.000000;,
  -0.999996;0.002671;0.000000;,
  -0.993651;0.112506;0.000000;;
  8;
  4;0,1,2,3;,
  4;3,2,4,5;,
  4;6,7,8,9;,
  4;9,8,10,10;,
  3;11,12,13;,
  3;13,12,14;,
  3;15,16,17;,
  3;17,16,18;;
 }
}
