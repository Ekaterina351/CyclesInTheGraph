@echo off
chcp 1251 > nul 
setlocal enabledelayedexpansion
set program=CyclesInTheGraph.exe

echo. > results.txt
echo 1 - ���� ���� � ����� �� ����� ���������. >> results.txt
echo. >> results.txt
%program% ./input1.csv ./output.txt >> results.txt 2>&1 
echo ������� ������: >> results.txt
type input1.csv >> results.txt
echo. >> results.txt
echo �������� ������: >> results.txt
type output.txt >> results.txt

echo. >> results.txt
echo. >> results.txt
echo 02 - ��� �����. ����� � ���������. >> results.txt
echo. >> results.txt
%program% ./input2.csv ./output.txt >> results.txt 2>&1 
echo ������� ������: >> results.txt
type input2.csv >> results.txt
echo. >> results.txt
echo �������� ������: >> results.txt
type output.txt >> results.txt

echo. >> results.txt
echo. >> results.txt
echo 03 - ����� ������ � �����. >> results.txt
echo. >> results.txt
%program% ./input3.csv ./output.txt >> results.txt 2>&1 
echo ������� ������: >> results.txt
type input3.csv >> results.txt
echo. >> results.txt
echo �������� ������: >> results.txt
type output.txt >> results.txt

echo. >> results.txt
echo. >> results.txt
echo 04 - � ����� ��� ������. >> results.txt
echo. >> results.txt
%program% ./input4.csv ./output.txt >> results.txt 2>&1 
echo ������� ������: >> results.txt
type input4.csv >> results.txt
echo. >> results.txt
echo �������� ������: >> results.txt
type output.txt >> results.txt

echo. >> results.txt
echo. >> results.txt
echo 05 - �������� ������� ������: � ��������� ��� �������� �������. >> results.txt
echo. >> results.txt
echo ������� ������: >> results.txt
type input5_empty_header_vertex_name.csv >> results.txt
echo. >> results.txt
echo ����� ������: >> results.txt
%program% ./input5_empty_header_vertex_name.csv ./output.txt >> results.txt 2>&1 

echo. >> results.txt
echo. >> results.txt
echo 06 - �������� ������� ������: ���������� ������� � ���������. >> results.txt
echo. >> results.txt
echo ������� ������: >> results.txt
type input6_duplicate_vetex_name.csv >> results.txt
echo. >> results.txt
echo ����� ������: >> results.txt
%program% ./input6_duplicate_vetex_name.csv ./output.txt >> results.txt 2>&1 

echo. >> results.txt
echo. >> results.txt
echo 07 - �������� ������� ������: ������ ������ � ���� �������.  >> results.txt
echo. >> results.txt
echo ������� ������: >> results.txt
type input7_empty_cell_in_body.csv >> results.txt
echo. >> results.txt
echo ����� ������: >> results.txt
%program% ./input7_empty_cell_in_body.csv ./output.txt >> results.txt 2>&1 
