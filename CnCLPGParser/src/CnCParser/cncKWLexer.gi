--
-- The Java KeyWord Lexer
--
%Options fp=CncKWLexer
%options package=CnCParser
%options template=KeywordTemplateF.gi

%Notice
/.
//
// This file is part of the CNC-C implementation and
// distributed under the Modified BSD License. 
// See LICENSE for details.
// 
// I AM A GENERATED FILE. PLEASE DO NOT CHANGE ME!!!
//
./
%End

%Include
    KWLexerFoldedCaseMapF.gi
%End

%Export

    T_ENV  
    T_UNSIGNED
    T_STRUCT

%End

%Terminals
    a    b    c    d    e    f    g    h    i    j    k    l    m
    n    o    p    q    r    s    t    u    v    w    x    y    z
%End

%Start
    KeyWord
%End

%Rules

    KeyWord ::= e n v /.$setResult($_T_ENV);./ 
    KeyWord ::= s t r u c t /.$setResult($_T_STRUCT);./
    KeyWord ::= u n s i g n e d /.$setResult($_T_UNSIGNED);./

%End
