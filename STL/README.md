STL Files
=====================

[中文版](STL文件)


This folder contains the STL files I used in this project.

- `mask.stl`: The mask with Chinese characters. I don't have a CNC carving machine so I printed it. Use a CNC to get a better result, if you have one.
  - When slicing, *flip the model* to make it facing down (to get a flat surface), then *rotate it 45 degree* (to avoid 45 degree printing marks).
  - Calibrate your flow rate to avoid any overextrusion. Overextrusion will fill the gap for the characters and lead to failure.
  - DO NOT use ironing.
  - Sand the surface with sandpapers. Use 400 => 600 => 1000 => 1500 grit to get a good result.
- `grid.stl`: The grid for blocking the LED lights.
- `case-bottom.stl` and `case-lid.stl`: The case for the ESP8266 Dev Kit.


STL文件
=========


本文件夹提供了项目中用到的STL文件。

- `mask.stl`：写有汉字的遮罩。这个遮罩用CNC雕刻机制作的效果最好，但我只有3D打印机，只能打印了。
  - 在切片前，将模型*翻转*至正面朝下（以获得平整的表面），并*旋转45度*（避免出现45度角的打印痕迹）。
  - 务必校准打印机的flow rate，避免过度挤出。过度挤出会填满汉字的缝隙，导致打印失败。
  - **不要使用ironing**。
  - 打印完毕后用砂纸打磨表面。建议采用400 => 600 => 1000 => 1500的顺序以获得较好的效果
- `grid.stl`：阻光用的格栅。
- `case-bottom.stl` 和 `case-lid.stl`：ESP8266开发板的外壳。
