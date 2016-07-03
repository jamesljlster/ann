##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=NNLIB
ConfigurationName      :=Debug
WorkspacePath          :=D:/CodeProject/CodeLite
ProjectPath            :=D:/CodeProject/CodeLite/NNLIB
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=James
Date                   :=24/06/2016
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=D:/Compiler/MinGW64/GCC5.3.0/mingw64/bin/g++.exe
SharedObjectLinkerName :=D:/Compiler/MinGW64/GCC5.3.0/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="NNLIB.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=D:/Compiler/MinGW64/GCC5.3.0/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := D:/Compiler/MinGW64/GCC5.3.0/mingw64/bin/ar.exe rcu
CXX      := D:/Compiler/MinGW64/GCC5.3.0/mingw64/bin/g++.exe
CC       := D:/Compiler/MinGW64/GCC5.3.0/mingw64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := D:/Compiler/MinGW64/GCC5.3.0/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/Alloc2DArray.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_TrainProc.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_MathCalc.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_IibFunc.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_IO.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_LearnFunc.c$(ObjectSuffix) $(IntermediateDirectory)/ActiveFunc.c$(ObjectSuffix) $(IntermediateDirectory)/MathProc.c$(ObjectSuffix) $(IntermediateDirectory)/CMDL_NNIO.c$(ObjectSuffix) \
	$(IntermediateDirectory)/CMDL_StringProc.c$(ObjectSuffix) $(IntermediateDirectory)/CMDL_UserInterface.c$(ObjectSuffix) $(IntermediateDirectory)/CMDL_Prediction.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_Prediction.c$(ObjectSuffix) $(IntermediateDirectory)/CMDL_CreateNN.c$(ObjectSuffix) $(IntermediateDirectory)/CMDL_SLearning.c$(ObjectSuffix) $(IntermediateDirectory)/KEEL_KWProc_Attribute.c$(ObjectSuffix) $(IntermediateDirectory)/KEEL_KWProc_Inputs.c$(ObjectSuffix) $(IntermediateDirectory)/KEEL_KWProc_Outputs.c$(ObjectSuffix) $(IntermediateDirectory)/KEEL_KWProc_Relation.c$(ObjectSuffix) \
	$(IntermediateDirectory)/KEEL_LibFunc.c$(ObjectSuffix) $(IntermediateDirectory)/KEEL_ReadDataset.c$(ObjectSuffix) $(IntermediateDirectory)/KEEL_StringProc.c$(ObjectSuffix) $(IntermediateDirectory)/CMDL_GetOutput.c$(ObjectSuffix) $(IntermediateDirectory)/CMDL_FindError.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_aFuncProc.c$(ObjectSuffix) $(IntermediateDirectory)/CMDL_SetActiveFunc.c$(ObjectSuffix) $(IntermediateDirectory)/CMDL_NormalizeData.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/Alloc2DArray.c$(ObjectSuffix): Alloc2DArray.c $(IntermediateDirectory)/Alloc2DArray.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/Alloc2DArray.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Alloc2DArray.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Alloc2DArray.c$(DependSuffix): Alloc2DArray.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Alloc2DArray.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Alloc2DArray.c$(DependSuffix) -MM "Alloc2DArray.c"

$(IntermediateDirectory)/Alloc2DArray.c$(PreprocessSuffix): Alloc2DArray.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Alloc2DArray.c$(PreprocessSuffix) "Alloc2DArray.c"

$(IntermediateDirectory)/NNLIB_TrainProc.c$(ObjectSuffix): NNLIB_TrainProc.c $(IntermediateDirectory)/NNLIB_TrainProc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/NNLIB_TrainProc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NNLIB_TrainProc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NNLIB_TrainProc.c$(DependSuffix): NNLIB_TrainProc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NNLIB_TrainProc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/NNLIB_TrainProc.c$(DependSuffix) -MM "NNLIB_TrainProc.c"

$(IntermediateDirectory)/NNLIB_TrainProc.c$(PreprocessSuffix): NNLIB_TrainProc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NNLIB_TrainProc.c$(PreprocessSuffix) "NNLIB_TrainProc.c"

$(IntermediateDirectory)/NNLIB_MathCalc.c$(ObjectSuffix): NNLIB_MathCalc.c $(IntermediateDirectory)/NNLIB_MathCalc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/NNLIB_MathCalc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NNLIB_MathCalc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NNLIB_MathCalc.c$(DependSuffix): NNLIB_MathCalc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NNLIB_MathCalc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/NNLIB_MathCalc.c$(DependSuffix) -MM "NNLIB_MathCalc.c"

$(IntermediateDirectory)/NNLIB_MathCalc.c$(PreprocessSuffix): NNLIB_MathCalc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NNLIB_MathCalc.c$(PreprocessSuffix) "NNLIB_MathCalc.c"

$(IntermediateDirectory)/NNLIB_IibFunc.c$(ObjectSuffix): NNLIB_IibFunc.c $(IntermediateDirectory)/NNLIB_IibFunc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/NNLIB_IibFunc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NNLIB_IibFunc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NNLIB_IibFunc.c$(DependSuffix): NNLIB_IibFunc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NNLIB_IibFunc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/NNLIB_IibFunc.c$(DependSuffix) -MM "NNLIB_IibFunc.c"

$(IntermediateDirectory)/NNLIB_IibFunc.c$(PreprocessSuffix): NNLIB_IibFunc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NNLIB_IibFunc.c$(PreprocessSuffix) "NNLIB_IibFunc.c"

$(IntermediateDirectory)/NNLIB_IO.c$(ObjectSuffix): NNLIB_IO.c $(IntermediateDirectory)/NNLIB_IO.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/NNLIB_IO.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NNLIB_IO.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NNLIB_IO.c$(DependSuffix): NNLIB_IO.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NNLIB_IO.c$(ObjectSuffix) -MF$(IntermediateDirectory)/NNLIB_IO.c$(DependSuffix) -MM "NNLIB_IO.c"

$(IntermediateDirectory)/NNLIB_IO.c$(PreprocessSuffix): NNLIB_IO.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NNLIB_IO.c$(PreprocessSuffix) "NNLIB_IO.c"

$(IntermediateDirectory)/NNLIB_LearnFunc.c$(ObjectSuffix): NNLIB_LearnFunc.c $(IntermediateDirectory)/NNLIB_LearnFunc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/NNLIB_LearnFunc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NNLIB_LearnFunc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NNLIB_LearnFunc.c$(DependSuffix): NNLIB_LearnFunc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NNLIB_LearnFunc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/NNLIB_LearnFunc.c$(DependSuffix) -MM "NNLIB_LearnFunc.c"

$(IntermediateDirectory)/NNLIB_LearnFunc.c$(PreprocessSuffix): NNLIB_LearnFunc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NNLIB_LearnFunc.c$(PreprocessSuffix) "NNLIB_LearnFunc.c"

$(IntermediateDirectory)/ActiveFunc.c$(ObjectSuffix): ActiveFunc.c $(IntermediateDirectory)/ActiveFunc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/ActiveFunc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ActiveFunc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ActiveFunc.c$(DependSuffix): ActiveFunc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ActiveFunc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ActiveFunc.c$(DependSuffix) -MM "ActiveFunc.c"

$(IntermediateDirectory)/ActiveFunc.c$(PreprocessSuffix): ActiveFunc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ActiveFunc.c$(PreprocessSuffix) "ActiveFunc.c"

$(IntermediateDirectory)/MathProc.c$(ObjectSuffix): MathProc.c $(IntermediateDirectory)/MathProc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/MathProc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MathProc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MathProc.c$(DependSuffix): MathProc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MathProc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/MathProc.c$(DependSuffix) -MM "MathProc.c"

$(IntermediateDirectory)/MathProc.c$(PreprocessSuffix): MathProc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MathProc.c$(PreprocessSuffix) "MathProc.c"

$(IntermediateDirectory)/CMDL_NNIO.c$(ObjectSuffix): CMDL_NNIO.c $(IntermediateDirectory)/CMDL_NNIO.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/CMDL_NNIO.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMDL_NNIO.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMDL_NNIO.c$(DependSuffix): CMDL_NNIO.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMDL_NNIO.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CMDL_NNIO.c$(DependSuffix) -MM "CMDL_NNIO.c"

$(IntermediateDirectory)/CMDL_NNIO.c$(PreprocessSuffix): CMDL_NNIO.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMDL_NNIO.c$(PreprocessSuffix) "CMDL_NNIO.c"

$(IntermediateDirectory)/CMDL_StringProc.c$(ObjectSuffix): CMDL_StringProc.c $(IntermediateDirectory)/CMDL_StringProc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/CMDL_StringProc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMDL_StringProc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMDL_StringProc.c$(DependSuffix): CMDL_StringProc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMDL_StringProc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CMDL_StringProc.c$(DependSuffix) -MM "CMDL_StringProc.c"

$(IntermediateDirectory)/CMDL_StringProc.c$(PreprocessSuffix): CMDL_StringProc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMDL_StringProc.c$(PreprocessSuffix) "CMDL_StringProc.c"

$(IntermediateDirectory)/CMDL_UserInterface.c$(ObjectSuffix): CMDL_UserInterface.c $(IntermediateDirectory)/CMDL_UserInterface.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/CMDL_UserInterface.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMDL_UserInterface.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMDL_UserInterface.c$(DependSuffix): CMDL_UserInterface.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMDL_UserInterface.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CMDL_UserInterface.c$(DependSuffix) -MM "CMDL_UserInterface.c"

$(IntermediateDirectory)/CMDL_UserInterface.c$(PreprocessSuffix): CMDL_UserInterface.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMDL_UserInterface.c$(PreprocessSuffix) "CMDL_UserInterface.c"

$(IntermediateDirectory)/CMDL_Prediction.c$(ObjectSuffix): CMDL_Prediction.c $(IntermediateDirectory)/CMDL_Prediction.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/CMDL_Prediction.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMDL_Prediction.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMDL_Prediction.c$(DependSuffix): CMDL_Prediction.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMDL_Prediction.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CMDL_Prediction.c$(DependSuffix) -MM "CMDL_Prediction.c"

$(IntermediateDirectory)/CMDL_Prediction.c$(PreprocessSuffix): CMDL_Prediction.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMDL_Prediction.c$(PreprocessSuffix) "CMDL_Prediction.c"

$(IntermediateDirectory)/NNLIB_Prediction.c$(ObjectSuffix): NNLIB_Prediction.c $(IntermediateDirectory)/NNLIB_Prediction.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/NNLIB_Prediction.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NNLIB_Prediction.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NNLIB_Prediction.c$(DependSuffix): NNLIB_Prediction.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NNLIB_Prediction.c$(ObjectSuffix) -MF$(IntermediateDirectory)/NNLIB_Prediction.c$(DependSuffix) -MM "NNLIB_Prediction.c"

$(IntermediateDirectory)/NNLIB_Prediction.c$(PreprocessSuffix): NNLIB_Prediction.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NNLIB_Prediction.c$(PreprocessSuffix) "NNLIB_Prediction.c"

$(IntermediateDirectory)/CMDL_CreateNN.c$(ObjectSuffix): CMDL_CreateNN.c $(IntermediateDirectory)/CMDL_CreateNN.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/CMDL_CreateNN.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMDL_CreateNN.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMDL_CreateNN.c$(DependSuffix): CMDL_CreateNN.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMDL_CreateNN.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CMDL_CreateNN.c$(DependSuffix) -MM "CMDL_CreateNN.c"

$(IntermediateDirectory)/CMDL_CreateNN.c$(PreprocessSuffix): CMDL_CreateNN.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMDL_CreateNN.c$(PreprocessSuffix) "CMDL_CreateNN.c"

$(IntermediateDirectory)/CMDL_SLearning.c$(ObjectSuffix): CMDL_SLearning.c $(IntermediateDirectory)/CMDL_SLearning.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/CMDL_SLearning.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMDL_SLearning.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMDL_SLearning.c$(DependSuffix): CMDL_SLearning.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMDL_SLearning.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CMDL_SLearning.c$(DependSuffix) -MM "CMDL_SLearning.c"

$(IntermediateDirectory)/CMDL_SLearning.c$(PreprocessSuffix): CMDL_SLearning.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMDL_SLearning.c$(PreprocessSuffix) "CMDL_SLearning.c"

$(IntermediateDirectory)/KEEL_KWProc_Attribute.c$(ObjectSuffix): KEEL_KWProc_Attribute.c $(IntermediateDirectory)/KEEL_KWProc_Attribute.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/KEEL_KWProc_Attribute.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KEEL_KWProc_Attribute.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KEEL_KWProc_Attribute.c$(DependSuffix): KEEL_KWProc_Attribute.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KEEL_KWProc_Attribute.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KEEL_KWProc_Attribute.c$(DependSuffix) -MM "KEEL_KWProc_Attribute.c"

$(IntermediateDirectory)/KEEL_KWProc_Attribute.c$(PreprocessSuffix): KEEL_KWProc_Attribute.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KEEL_KWProc_Attribute.c$(PreprocessSuffix) "KEEL_KWProc_Attribute.c"

$(IntermediateDirectory)/KEEL_KWProc_Inputs.c$(ObjectSuffix): KEEL_KWProc_Inputs.c $(IntermediateDirectory)/KEEL_KWProc_Inputs.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/KEEL_KWProc_Inputs.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KEEL_KWProc_Inputs.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KEEL_KWProc_Inputs.c$(DependSuffix): KEEL_KWProc_Inputs.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KEEL_KWProc_Inputs.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KEEL_KWProc_Inputs.c$(DependSuffix) -MM "KEEL_KWProc_Inputs.c"

$(IntermediateDirectory)/KEEL_KWProc_Inputs.c$(PreprocessSuffix): KEEL_KWProc_Inputs.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KEEL_KWProc_Inputs.c$(PreprocessSuffix) "KEEL_KWProc_Inputs.c"

$(IntermediateDirectory)/KEEL_KWProc_Outputs.c$(ObjectSuffix): KEEL_KWProc_Outputs.c $(IntermediateDirectory)/KEEL_KWProc_Outputs.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/KEEL_KWProc_Outputs.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KEEL_KWProc_Outputs.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KEEL_KWProc_Outputs.c$(DependSuffix): KEEL_KWProc_Outputs.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KEEL_KWProc_Outputs.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KEEL_KWProc_Outputs.c$(DependSuffix) -MM "KEEL_KWProc_Outputs.c"

$(IntermediateDirectory)/KEEL_KWProc_Outputs.c$(PreprocessSuffix): KEEL_KWProc_Outputs.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KEEL_KWProc_Outputs.c$(PreprocessSuffix) "KEEL_KWProc_Outputs.c"

$(IntermediateDirectory)/KEEL_KWProc_Relation.c$(ObjectSuffix): KEEL_KWProc_Relation.c $(IntermediateDirectory)/KEEL_KWProc_Relation.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/KEEL_KWProc_Relation.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KEEL_KWProc_Relation.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KEEL_KWProc_Relation.c$(DependSuffix): KEEL_KWProc_Relation.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KEEL_KWProc_Relation.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KEEL_KWProc_Relation.c$(DependSuffix) -MM "KEEL_KWProc_Relation.c"

$(IntermediateDirectory)/KEEL_KWProc_Relation.c$(PreprocessSuffix): KEEL_KWProc_Relation.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KEEL_KWProc_Relation.c$(PreprocessSuffix) "KEEL_KWProc_Relation.c"

$(IntermediateDirectory)/KEEL_LibFunc.c$(ObjectSuffix): KEEL_LibFunc.c $(IntermediateDirectory)/KEEL_LibFunc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/KEEL_LibFunc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KEEL_LibFunc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KEEL_LibFunc.c$(DependSuffix): KEEL_LibFunc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KEEL_LibFunc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KEEL_LibFunc.c$(DependSuffix) -MM "KEEL_LibFunc.c"

$(IntermediateDirectory)/KEEL_LibFunc.c$(PreprocessSuffix): KEEL_LibFunc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KEEL_LibFunc.c$(PreprocessSuffix) "KEEL_LibFunc.c"

$(IntermediateDirectory)/KEEL_ReadDataset.c$(ObjectSuffix): KEEL_ReadDataset.c $(IntermediateDirectory)/KEEL_ReadDataset.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/KEEL_ReadDataset.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KEEL_ReadDataset.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KEEL_ReadDataset.c$(DependSuffix): KEEL_ReadDataset.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KEEL_ReadDataset.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KEEL_ReadDataset.c$(DependSuffix) -MM "KEEL_ReadDataset.c"

$(IntermediateDirectory)/KEEL_ReadDataset.c$(PreprocessSuffix): KEEL_ReadDataset.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KEEL_ReadDataset.c$(PreprocessSuffix) "KEEL_ReadDataset.c"

$(IntermediateDirectory)/KEEL_StringProc.c$(ObjectSuffix): KEEL_StringProc.c $(IntermediateDirectory)/KEEL_StringProc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/KEEL_StringProc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KEEL_StringProc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KEEL_StringProc.c$(DependSuffix): KEEL_StringProc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KEEL_StringProc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KEEL_StringProc.c$(DependSuffix) -MM "KEEL_StringProc.c"

$(IntermediateDirectory)/KEEL_StringProc.c$(PreprocessSuffix): KEEL_StringProc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KEEL_StringProc.c$(PreprocessSuffix) "KEEL_StringProc.c"

$(IntermediateDirectory)/CMDL_GetOutput.c$(ObjectSuffix): CMDL_GetOutput.c $(IntermediateDirectory)/CMDL_GetOutput.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/CMDL_GetOutput.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMDL_GetOutput.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMDL_GetOutput.c$(DependSuffix): CMDL_GetOutput.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMDL_GetOutput.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CMDL_GetOutput.c$(DependSuffix) -MM "CMDL_GetOutput.c"

$(IntermediateDirectory)/CMDL_GetOutput.c$(PreprocessSuffix): CMDL_GetOutput.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMDL_GetOutput.c$(PreprocessSuffix) "CMDL_GetOutput.c"

$(IntermediateDirectory)/CMDL_FindError.c$(ObjectSuffix): CMDL_FindError.c $(IntermediateDirectory)/CMDL_FindError.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/CMDL_FindError.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMDL_FindError.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMDL_FindError.c$(DependSuffix): CMDL_FindError.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMDL_FindError.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CMDL_FindError.c$(DependSuffix) -MM "CMDL_FindError.c"

$(IntermediateDirectory)/CMDL_FindError.c$(PreprocessSuffix): CMDL_FindError.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMDL_FindError.c$(PreprocessSuffix) "CMDL_FindError.c"

$(IntermediateDirectory)/NNLIB_aFuncProc.c$(ObjectSuffix): NNLIB_aFuncProc.c $(IntermediateDirectory)/NNLIB_aFuncProc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/NNLIB_aFuncProc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NNLIB_aFuncProc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NNLIB_aFuncProc.c$(DependSuffix): NNLIB_aFuncProc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NNLIB_aFuncProc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/NNLIB_aFuncProc.c$(DependSuffix) -MM "NNLIB_aFuncProc.c"

$(IntermediateDirectory)/NNLIB_aFuncProc.c$(PreprocessSuffix): NNLIB_aFuncProc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NNLIB_aFuncProc.c$(PreprocessSuffix) "NNLIB_aFuncProc.c"

$(IntermediateDirectory)/CMDL_SetActiveFunc.c$(ObjectSuffix): CMDL_SetActiveFunc.c $(IntermediateDirectory)/CMDL_SetActiveFunc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/CMDL_SetActiveFunc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMDL_SetActiveFunc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMDL_SetActiveFunc.c$(DependSuffix): CMDL_SetActiveFunc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMDL_SetActiveFunc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CMDL_SetActiveFunc.c$(DependSuffix) -MM "CMDL_SetActiveFunc.c"

$(IntermediateDirectory)/CMDL_SetActiveFunc.c$(PreprocessSuffix): CMDL_SetActiveFunc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMDL_SetActiveFunc.c$(PreprocessSuffix) "CMDL_SetActiveFunc.c"

$(IntermediateDirectory)/CMDL_NormalizeData.c$(ObjectSuffix): CMDL_NormalizeData.c $(IntermediateDirectory)/CMDL_NormalizeData.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/CMDL_NormalizeData.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMDL_NormalizeData.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMDL_NormalizeData.c$(DependSuffix): CMDL_NormalizeData.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMDL_NormalizeData.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CMDL_NormalizeData.c$(DependSuffix) -MM "CMDL_NormalizeData.c"

$(IntermediateDirectory)/CMDL_NormalizeData.c$(PreprocessSuffix): CMDL_NormalizeData.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMDL_NormalizeData.c$(PreprocessSuffix) "CMDL_NormalizeData.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


