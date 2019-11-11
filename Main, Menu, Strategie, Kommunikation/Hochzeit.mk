##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Hochzeit
ConfigurationName      :=Debug
WorkspacePath          :=/home/pi/Desktop/Hochzeit/Hochzeit
ProjectPath            :=/home/pi/Desktop/Hochzeit/Hochzeit/Hochzeit
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=27/09/19
CodeLitePath           :=/home/pi/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
ObjectsFileList        :="Hochzeit.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -g -O0 -Wall -lwiringPi -lncurses
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)/usr/include/SFML 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)sfml-graphics $(LibrarySwitch)sfml-window $(LibrarySwitch)sfml-system 
ArLibs                 :=  "sfml-graphics" "sfml-window" "sfml-system" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/include/SFML 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall -lwiringPi -lncurses $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall -lwiringPi -lncurses $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/strategie.cpp$(ObjectSuffix) $(IntermediateDirectory)/puck.cpp$(ObjectSuffix) $(IntermediateDirectory)/striker.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_V2_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/grafik.cpp$(ObjectSuffix) $(IntermediateDirectory)/i2cControl.cpp$(ObjectSuffix) $(IntermediateDirectory)/lcdDriver.cpp$(ObjectSuffix) $(IntermediateDirectory)/strategieTest.cpp$(ObjectSuffix) $(IntermediateDirectory)/pi2c.cpp$(ObjectSuffix) 



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
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/strategie.cpp$(ObjectSuffix): strategie.cpp $(IntermediateDirectory)/strategie.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/Desktop/Hochzeit/Hochzeit/Hochzeit/strategie.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/strategie.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/strategie.cpp$(DependSuffix): strategie.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/strategie.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/strategie.cpp$(DependSuffix) -MM strategie.cpp

$(IntermediateDirectory)/strategie.cpp$(PreprocessSuffix): strategie.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/strategie.cpp$(PreprocessSuffix) strategie.cpp

$(IntermediateDirectory)/puck.cpp$(ObjectSuffix): puck.cpp $(IntermediateDirectory)/puck.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/Desktop/Hochzeit/Hochzeit/Hochzeit/puck.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/puck.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/puck.cpp$(DependSuffix): puck.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/puck.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/puck.cpp$(DependSuffix) -MM puck.cpp

$(IntermediateDirectory)/puck.cpp$(PreprocessSuffix): puck.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/puck.cpp$(PreprocessSuffix) puck.cpp

$(IntermediateDirectory)/striker.cpp$(ObjectSuffix): striker.cpp $(IntermediateDirectory)/striker.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/Desktop/Hochzeit/Hochzeit/Hochzeit/striker.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/striker.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/striker.cpp$(DependSuffix): striker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/striker.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/striker.cpp$(DependSuffix) -MM striker.cpp

$(IntermediateDirectory)/striker.cpp$(PreprocessSuffix): striker.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/striker.cpp$(PreprocessSuffix) striker.cpp

$(IntermediateDirectory)/up_V2_main.cpp$(ObjectSuffix): ../V2/main.cpp $(IntermediateDirectory)/up_V2_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/Desktop/Hochzeit/Hochzeit/V2/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_V2_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_V2_main.cpp$(DependSuffix): ../V2/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_V2_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_V2_main.cpp$(DependSuffix) -MM ../V2/main.cpp

$(IntermediateDirectory)/up_V2_main.cpp$(PreprocessSuffix): ../V2/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_V2_main.cpp$(PreprocessSuffix) ../V2/main.cpp

$(IntermediateDirectory)/grafik.cpp$(ObjectSuffix): grafik.cpp $(IntermediateDirectory)/grafik.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/Desktop/Hochzeit/Hochzeit/Hochzeit/grafik.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/grafik.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/grafik.cpp$(DependSuffix): grafik.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/grafik.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/grafik.cpp$(DependSuffix) -MM grafik.cpp

$(IntermediateDirectory)/grafik.cpp$(PreprocessSuffix): grafik.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/grafik.cpp$(PreprocessSuffix) grafik.cpp

$(IntermediateDirectory)/i2cControl.cpp$(ObjectSuffix): i2cControl.cpp $(IntermediateDirectory)/i2cControl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/Desktop/Hochzeit/Hochzeit/Hochzeit/i2cControl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/i2cControl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/i2cControl.cpp$(DependSuffix): i2cControl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/i2cControl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/i2cControl.cpp$(DependSuffix) -MM i2cControl.cpp

$(IntermediateDirectory)/i2cControl.cpp$(PreprocessSuffix): i2cControl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/i2cControl.cpp$(PreprocessSuffix) i2cControl.cpp

$(IntermediateDirectory)/lcdDriver.cpp$(ObjectSuffix): lcdDriver.cpp $(IntermediateDirectory)/lcdDriver.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/Desktop/Hochzeit/Hochzeit/Hochzeit/lcdDriver.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lcdDriver.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lcdDriver.cpp$(DependSuffix): lcdDriver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lcdDriver.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/lcdDriver.cpp$(DependSuffix) -MM lcdDriver.cpp

$(IntermediateDirectory)/lcdDriver.cpp$(PreprocessSuffix): lcdDriver.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lcdDriver.cpp$(PreprocessSuffix) lcdDriver.cpp

$(IntermediateDirectory)/strategieTest.cpp$(ObjectSuffix): strategieTest.cpp $(IntermediateDirectory)/strategieTest.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/Desktop/Hochzeit/Hochzeit/Hochzeit/strategieTest.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/strategieTest.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/strategieTest.cpp$(DependSuffix): strategieTest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/strategieTest.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/strategieTest.cpp$(DependSuffix) -MM strategieTest.cpp

$(IntermediateDirectory)/strategieTest.cpp$(PreprocessSuffix): strategieTest.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/strategieTest.cpp$(PreprocessSuffix) strategieTest.cpp

$(IntermediateDirectory)/pi2c.cpp$(ObjectSuffix): pi2c.cpp $(IntermediateDirectory)/pi2c.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pi/Desktop/Hochzeit/Hochzeit/Hochzeit/pi2c.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pi2c.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pi2c.cpp$(DependSuffix): pi2c.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pi2c.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/pi2c.cpp$(DependSuffix) -MM pi2c.cpp

$(IntermediateDirectory)/pi2c.cpp$(PreprocessSuffix): pi2c.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pi2c.cpp$(PreprocessSuffix) pi2c.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


