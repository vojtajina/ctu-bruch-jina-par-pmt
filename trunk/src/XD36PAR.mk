##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=XD36PAR
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "C:\cygwin\home\Vojta\xd36par"
ProjectPath            := "C:\cygwin\home\Vojta\xd36par\src"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Vojta
Date                   :=04/04/10
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=makedir
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
UNIT_TEST_PP_SRC_DIR:=C:\Program Files\CodeLite\UnitTest
CodeLiteDir:=C:\Program Files\CodeLite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/configuration$(ObjectSuffix) $(IntermediateDirectory)/task$(ObjectSuffix) $(IntermediateDirectory)/priority_queue$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/cygwin/home/Vojta/xd36par/src/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "C:/cygwin/home/Vojta/xd36par/src/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "C:/cygwin/home/Vojta/xd36par/src/main.cpp"

$(IntermediateDirectory)/configuration$(ObjectSuffix): configuration.cpp $(IntermediateDirectory)/configuration$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/cygwin/home/Vojta/xd36par/src/configuration.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/configuration$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/configuration$(DependSuffix): configuration.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/configuration$(ObjectSuffix) -MF$(IntermediateDirectory)/configuration$(DependSuffix) -MM "C:/cygwin/home/Vojta/xd36par/src/configuration.cpp"

$(IntermediateDirectory)/configuration$(PreprocessSuffix): configuration.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/configuration$(PreprocessSuffix) "C:/cygwin/home/Vojta/xd36par/src/configuration.cpp"

$(IntermediateDirectory)/task$(ObjectSuffix): task.cpp $(IntermediateDirectory)/task$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/cygwin/home/Vojta/xd36par/src/task.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/task$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/task$(DependSuffix): task.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/task$(ObjectSuffix) -MF$(IntermediateDirectory)/task$(DependSuffix) -MM "C:/cygwin/home/Vojta/xd36par/src/task.cpp"

$(IntermediateDirectory)/task$(PreprocessSuffix): task.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/task$(PreprocessSuffix) "C:/cygwin/home/Vojta/xd36par/src/task.cpp"

$(IntermediateDirectory)/priority_queue$(ObjectSuffix): priority_queue.cpp $(IntermediateDirectory)/priority_queue$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "C:/cygwin/home/Vojta/xd36par/src/priority_queue.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/priority_queue$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/priority_queue$(DependSuffix): priority_queue.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/priority_queue$(ObjectSuffix) -MF$(IntermediateDirectory)/priority_queue$(DependSuffix) -MM "C:/cygwin/home/Vojta/xd36par/src/priority_queue.cpp"

$(IntermediateDirectory)/priority_queue$(PreprocessSuffix): priority_queue.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/priority_queue$(PreprocessSuffix) "C:/cygwin/home/Vojta/xd36par/src/priority_queue.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/configuration$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/configuration$(DependSuffix)
	$(RM) $(IntermediateDirectory)/configuration$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/task$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/task$(DependSuffix)
	$(RM) $(IntermediateDirectory)/task$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/priority_queue$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/priority_queue$(DependSuffix)
	$(RM) $(IntermediateDirectory)/priority_queue$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe


