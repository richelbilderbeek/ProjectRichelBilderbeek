#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm

../ToolTestTwoDigitNewickConsole-build-desktop/./TestTwoDigitNewickDesktop "(2,2)" 10
../ToolTestTwoDigitNewickConsole-build-desktop/./TestTwoDigitNewickDesktop "(((((((((((2,2),2),2),2),2),2),2),2),2),2),2)" 10
../ToolTestTwoDigitNewickConsole-build-desktop/./TestTwoDigitNewickDesktop "((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2)" 10
../ToolTestTwoDigitNewickConsole-build-desktop/./TestTwoDigitNewickDesktop "(((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2)" 10

../ToolTestTwoDigitNewickConsole-build-desktop/./TestTwoDigitNewickDesktop "((((((((2,2),2),10),2),10),2),10),2)" 10

../ToolTestTwoDigitNewickConsole-build-desktop/./TestTwoDigitNewickDesktop "((((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2),2)" 10
../ToolTestTwoDigitNewickConsole-build-desktop/./TestTwoDigitNewickDesktop "(((((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2),2),2)" 10

#Throws bad alloc
#../ToolTestTwoDigitNewickConsole-build-desktop/./TestTwoDigitNewickDesktop "((((((((((((((2,2),2),2),2),2),2),2),10),2),2),10),2),10),2)" 10

