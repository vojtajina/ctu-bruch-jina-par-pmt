##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=XD36PAR
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "C:\Users\Vojta\CodeLiteWorkspace\Default"
ProjectPath            := "C:\Users\Vojta\CodeLiteWorkspace\Default\XD36PAR"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Vojta
Date                   :=04/02/10
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=
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
PreprocessOnlySwitch   :=
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
	@$(MakeDirCommand) "./Debug"
	$(CompilerName) $(SourceSwitch) "C:/Users/Vojta/CodeLiteWorkspace/Default/XD36PAR/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(MakeDirCommand) "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "C:/Users/Vojta/CodeLiteWorkspace/Default/XD36PAR/main.cpp"

$(IntermediateDirectory)/configuration$(ObjectSuffix): configuration.cpp $(IntermediateDirectory)/configuration$(DependSuffix)
	@$(MakeDirCommand) "./Debug"
	$(CompilerName) $(SourceSwitch) "C:/Users/Vojta/CodeLiteWorkspace/Default/XD36PAR/configuration.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/configuration$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/configuration$(DependSuffix): configuration.cpp
	@$(MakeDirCommand) "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/configuration$(ObjectSuffix) -MF$(IntermediateDirectory)/configuration$(DependSuffix) -MM "C:/Users/Vojta/CodeLiteWorkspace/Default/XD36PAR/configuration.cpp"

$(IntermediateDirectory)/task$(ObjectSuffix): task.cpp $(IntermediateDirectory)/task$(DependSuffix)
	@$(MakeDirCommand) "./Debug"
	$(CompilerName) $(SourceSwitch) "C:/Users/Vojta/CodeLiteWorkspace/Default/XD36PAR/task.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/task$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/task$(DependSuffix): task.cpp
	@$(MakeDirCommand) "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/task$(ObjectSuffix) -MF$(IntermediateDirectory)/task$(DependSuffix) -MM "C:/Users/Vojta/CodeLiteWorkspace/Default/XD36PAR/task.cpp"

$(IntermediateDirectory)/priority_queue$(ObjectSuffix): priority_queue.cpp $(IntermediateDirectory)/priority_queue$(DependSuffix)
	@$(MakeDirCommand) "./Debug"
	$(CompilerName) $(SourceSwitch) "C:/Users/Vojta/CodeLiteWorkspace/Default/XD36PAR/priority_queue.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/priority_queue$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/priority_queue$(DependSuffix): priority_queue.cpp
	@$(MakeDirCommand) "./Debug"
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/priority_queue$(ObjectSuffix) -MF$(IntermediateDirectory)/priority_queue$(DependSuffix) -MM "C:/Users/Vojta/CodeLiteWorkspace/Default/XD36PAR/priority_queue.cpp"


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


