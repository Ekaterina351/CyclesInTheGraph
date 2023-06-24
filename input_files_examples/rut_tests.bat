@echo off
chcp 1251 > nul 
setlocal enabledelayedexpansion
set program=CyclesInTheGraph.exe

echo. > results.txt
echo 1 - Îäèí öèêë â ãðàôå ñî âñåìè âåðøèíàìè. >> results.txt
echo. >> results.txt
%program% ./input1.csv ./output.txt >> results.txt 2>&1 
echo ÂÕÎÄÍÛÅ ÄÀÍÍÛÅ: >> results.txt
type input1.csv >> results.txt
echo. >> results.txt
echo ÂÛÕÎÄÍÛÅ ÄÀÍÍÛÅ: >> results.txt
type output.txt >> results.txt

echo. >> results.txt
echo. >> results.txt
echo 02 - Äâà öèêëà. Îáùèé è ÷àñòè÷íûé. >> results.txt
echo. >> results.txt
%program% ./input2.csv ./output.txt >> results.txt 2>&1 
echo ÂÕÎÄÍÛÅ ÄÀÍÍÛÅ: >> results.txt
type input2.csv >> results.txt
echo. >> results.txt
echo ÂÛÕÎÄÍÛÅ ÄÀÍÍÛÅ: >> results.txt
type output.txt >> results.txt

echo. >> results.txt
echo. >> results.txt
echo 03 - Ìíîãî öèêëîâ â ãðàôå. >> results.txt
echo. >> results.txt
%program% ./input3.csv ./output.txt >> results.txt 2>&1 
echo ÂÕÎÄÍÛÅ ÄÀÍÍÛÅ: >> results.txt
type input3.csv >> results.txt
echo. >> results.txt
echo ÂÛÕÎÄÍÛÅ ÄÀÍÍÛÅ: >> results.txt
type output.txt >> results.txt

echo. >> results.txt
echo. >> results.txt
echo 04 - Â ãðàôå íåò öèêëîâ. >> results.txt
echo. >> results.txt
%program% ./input4.csv ./output.txt >> results.txt 2>&1 
echo ÂÕÎÄÍÛÅ ÄÀÍÍÛÅ: >> results.txt
type input4.csv >> results.txt
echo. >> results.txt
echo ÂÛÕÎÄÍÛÅ ÄÀÍÍÛÅ: >> results.txt
type output.txt >> results.txt

echo. >> results.txt
echo. >> results.txt
echo 05 - Íåâåðíûå âõîäíûå äàííûå: Â çàãîëîâêå íåò íàçâàíèÿ âåðøèíû. >> results.txt
echo. >> results.txt
echo ÂÕÎÄÍÛÅ ÄÀÍÍÛÅ: >> results.txt
type input5_empty_header_vertex_name.csv >> results.txt
echo. >> results.txt
echo ÂÛÂÎÄ ÎØÈÁÊÈ: >> results.txt
%program% ./input5_empty_header_vertex_name.csv ./output.txt >> results.txt 2>&1 

echo. >> results.txt
echo. >> results.txt
echo 06 - Íåâåðíûå âõîäíûå äàííûå: Ïîâòîðåíèå âåðøèíû â çàãîëîâêå. >> results.txt
echo. >> results.txt
echo ÂÕÎÄÍÛÅ ÄÀÍÍÛÅ: >> results.txt
type input6_duplicate_vetex_name.csv >> results.txt
echo. >> results.txt
echo ÂÛÂÎÄ ÎØÈÁÊÈ: >> results.txt
%program% ./input6_duplicate_vetex_name.csv ./output.txt >> results.txt 2>&1 

echo. >> results.txt
echo. >> results.txt
echo 07 - Íåâåðíûå âõîäíûå äàííûå: Ïóñòàÿ êëåòêà â òåëå ìàòðèöû.  >> results.txt
echo. >> results.txt
echo ÂÕÎÄÍÛÅ ÄÀÍÍÛÅ: >> results.txt
type input7_empty_cell_in_body.csv >> results.txt
echo. >> results.txt
echo ÂÛÂÎÄ ÎØÈÁÊÈ: >> results.txt
%program% ./input7_empty_cell_in_body.csv ./output.txt >> results.txt 2>&1 
