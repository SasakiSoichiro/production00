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
 6.72431;-8.64157;3.74145;,
 6.71035;-8.63858;-3.07685;,
 6.73258;1.27484;-3.07256;,
 6.74654;1.27185;3.74575;,
 3.39412;7.41732;-3.06302;,
 3.40813;7.41433;3.75528;,
 -3.53381;7.96037;-2.85501;,
 -3.52066;7.95756;3.57613;,
 0.06701;1.28971;-2.86530;,
 0.08017;1.28688;3.56581;,
 0.04478;-8.62372;-2.86960;,
 0.05795;-8.62654;3.56151;;
 
 10;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,1,0;,
 4;1,10,8,2;,
 4;2,8,6,4;,
 4;11,0,3,9;,
 4;9,3,5,7;;
 
 MeshMaterialList {
  7;
  10;
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.019200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.434000;0.010416;0.000000;;
  }
  Material {
   0.380000;0.558400;0.558400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.143925;0.211494;0.211494;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.037600;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.021573;0.000000;0.459000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.671200;0.153600;0.169600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.171995;0.039360;0.043460;;
  }
 }
 MeshNormals {
  29;
  0.999995;-0.002242;-0.002049;,
  0.999995;-0.002242;-0.002049;,
  0.969453;0.245271;-0.001880;,
  0.969455;0.245261;-0.001880;,
  0.548390;0.836222;-0.000759;,
  0.548412;0.836208;-0.000759;,
  0.078154;0.996941;0.000276;,
  0.078154;0.996941;0.000276;,
  -0.879977;-0.475014;0.001592;,
  -0.879977;-0.475014;0.001592;,
  -0.969800;-0.243895;0.001878;,
  -0.969802;-0.243885;0.001878;,
  -0.999995;0.002241;0.002048;,
  -0.999995;0.002241;0.002048;,
  -0.002242;-0.999997;-0.000433;,
  -0.002242;-0.999997;-0.000433;,
  -0.002242;-0.999997;-0.000433;,
  -0.002242;-0.999997;-0.000433;,
  -0.031077;0.000503;-0.999517;,
  -0.031124;-0.008495;-0.999479;,
  -0.031110;-0.005916;-0.999498;,
  -0.031157;-0.015330;-0.999397;,
  -0.031157;-0.015330;-0.999397;,
  -0.026984;-0.000373;0.999636;,
  -0.026984;-0.000373;0.999636;,
  -0.027017;-0.006792;0.999612;,
  -0.027030;-0.009372;0.999591;,
  -0.027064;-0.016207;0.999502;,
  -0.027064;-0.016207;0.999502;;
  10;
  4;0,1,2,3;,
  4;3,2,4,5;,
  4;5,4,6,7;,
  4;8,9,10,11;,
  4;11,10,12,13;,
  4;14,15,16,17;,
  4;18,18,19,20;,
  4;20,19,21,22;,
  4;23,24,25,26;,
  4;26,25,27,28;;
 }
}
