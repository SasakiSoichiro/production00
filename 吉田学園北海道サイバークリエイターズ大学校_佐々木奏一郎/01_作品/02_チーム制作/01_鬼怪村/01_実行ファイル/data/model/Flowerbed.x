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
 32;
 14.71176;7.93460;-50.01500;,
 19.80500;7.93460;-50.01500;,
 19.80500;0.09460;-50.01500;,
 14.85662;0.09460;-50.01500;,
 14.64156;7.93460;50.01500;,
 14.78642;0.09460;50.01500;,
 19.80500;0.09460;50.01500;,
 19.80500;7.93460;50.01500;,
 -14.77779;0.09460;-50.01500;,
 -19.80500;0.09460;-50.01500;,
 -19.80500;7.93460;-50.01500;,
 -14.31838;7.93460;-50.01500;,
 -14.29364;7.93460;50.01500;,
 -19.80500;7.93460;50.01500;,
 -19.80500;0.09460;50.01500;,
 -14.75305;0.09460;50.01500;,
 19.80500;7.93460;43.87020;,
 19.80500;0.09460;44.83284;,
 -19.80500;7.93460;43.87697;,
 -19.80500;0.09460;44.83960;,
 14.64588;7.93460;43.87109;,
 -14.29516;7.93460;43.87602;,
 19.80500;0.09460;-45.03240;,
 19.80500;7.93460;-44.15984;,
 -19.80500;7.93460;-44.15306;,
 -19.80500;0.09460;-45.02564;,
 14.70765;7.93460;-44.15896;,
 -14.31693;7.93460;-44.15400;,
 -15.39000;7.98011;44.05283;,
 15.39000;7.98011;44.05283;,
 15.39000;7.98011;-44.05283;,
 -15.39000;7.98011;-44.05283;;
 
 21;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,0,3;,
 4;12,13,14,15;,
 4;12,15,5,4;,
 4;16,7,6,17;,
 4;18,19,14,13;,
 4;16,20,4,7;,
 4;18,13,12,21;,
 4;21,12,4,20;,
 4;22,2,1,23;,
 4;22,23,16,17;,
 4;24,10,9,25;,
 4;24,25,19,18;,
 4;23,1,0,26;,
 4;23,26,20,16;,
 4;27,11,10,24;,
 4;27,24,18,21;,
 4;26,0,11,27;,
 4;28,29,30,31;;
 
 MeshMaterialList {
  2;
  21;
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
  1;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Downloads\\renga.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Downloads\\soil.jpg";
   }
  }
 }
 MeshNormals {
  23;
  -0.000001;0.000000;-1.000000;,
  0.000001;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  0.000000;1.000000;0.000000;;
  21;
  4;4,1,1,4;,
  4;5,5,2,2;,
  4;6,0,0,6;,
  4;6,6,4,4;,
  4;7,3,3,7;,
  4;7,7,5,5;,
  4;9,15,15,9;,
  4;8,8,8,8;,
  4;10,10,10,10;,
  4;16,10,10,11;,
  4;11,10,10,10;,
  4;12,17,17,12;,
  4;12,12,9,9;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;10,10,18,13;,
  4;10,13,10,10;,
  4;14,19,20,21;,
  4;14,21,16,11;,
  4;13,18,19,14;,
  4;22,22,22,22;;
 }
}
