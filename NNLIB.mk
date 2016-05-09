##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=NNLIB
ConfigurationName      :=Debug
WorkspacePath          := "D:\CodeProject\CodeLite"
ProjectPath            := "D:\CodeProject\CodeLite\NNLIB"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=James
Date                   :=07/05/2016
CodeLitePath           :="C:\Program Files\CodeLite"
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
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/NN.c$(ObjectSuffix) $(IntermediateDirectory)/Alloc2DArray.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_TrainProc.c$(ObjectSuffix) $(IntermediateDirectory)/NNTraining.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_MathCalc.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_IibFunc.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_IO.c$(ObjectSuffix) $(IntermediateDirectory)/NNLIB_LearnFunc.c$(ObjectSuffix) $(IntermediateDirectory)/ActiveFunc.c$(ObjectSuffix) \
	$(IntermediateDirectory)/MathProc.c$(ObjectSuffix) 



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

$(IntermediateDirectory)/NN.c$(ObjectSuffix): NN.c $(IntermediateDirectory)/NN.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/NN.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NN.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NN.c$(DependSuffix): NN.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NN.c$(ObjectSuffix) -MF$(IntermediateDirectory)/NN.c$(DependSuffix) -MM "NN.c"

$(IntermediateDirectory)/NN.c$(PreprocessSuffix): NN.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NN.c$(PreprocessSuffix) "NN.c"

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

$(IntermediateDirectory)/NNTraining.c$(ObjectSuffix): NNTraining.c $(IntermediateDirectory)/NNTraining.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/CodeProject/CodeLite/NNLIB/NNTraining.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NNTraining.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NNTraining.c$(DependSuffix): NNTraining.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NNTraining.c$(ObjectSuffix) -MF$(IntermediateDirectory)/NNTraining.c$(DependSuffix) -MM "NNTraining.c"

$(IntermediateDirectory)/NNTraining.c$(PreprocessSuffix): NNTraining.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NNTraining.c$(PreprocessSuffix) "NNTraining.c"

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


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


