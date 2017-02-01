####################################################################################################
# README
#
#       This makefile template allows you to build both debug and release builds using a different
#       folder for each for all output files (i.e. dep and object files).
#
#       Invoke using any of the following:
#
#           make (builds debug by default)
#           make debug
#           make release
#           make remake
#           make all
#
#
#       Simply fill out the 'General info' section below to get started. Source files are 
#       automatically collected by searching the specified source directories.
#
#
#


####################################################################################################
# General info
#
BINARY_NAME 	    = MyAppName             # the name of your binary
CFLAGS 			    = -I.                   # build compiler flags
DEBUG_CFLAGS	    = -DDEBUG -g            # debug build compiler flags
RELEASE_CFLAGS	    = -O3 -DNDEBUG          # release build compiler flags
LIBS 			    = -lSDL2                # libs you want to link against (e.g. -lSDL2)
BUILD_DIR_PREFIX    = build                 # The build folder prefex for all builds
DEBUG_DIR_PREFIX    = debug                 # the debug build folder prefix
RELEASE_DIR_PREFIX  = release               # the release build folder prefix
SRC_DIRS		= 	. \                     # all the folders containing your source files
					myFolder1 \
                    myFolder2 \
                    myFolder3


# You probably don't need to modify anything below this note!


####################################################################################################
# Files (auto generated from SRC_DIRS)
#
VPATH			= $(SRC_DIRS) # VPATH is a special make variable allowing any 'current dir' operations to also work on the dirs listed in VPATH
SRC_FILES 		= $(foreach SRC_DIR, $(SRC_DIRS), $(wildcard $(SRC_DIR)/*.cpp)) # This crazy line iterates SRC_DIRS and extracts all the cpp files from each dir
OBJ_FILES 		= $(SRC_FILES:.cpp=.o)


####################################################################################################
# Debug info
#
DEBUG_BUILD_DIR = $(BUILD_DIR_PREFIX)/$(DEBUG_DIR_PREFIX)
DEBUG_BINARY	= $(DEBUG_BUILD_DIR)/$(BINARY_NAME)
DEBUG_OBJ_FILES = $(addprefix $(DEBUG_BUILD_DIR)/, $(notdir $(OBJ_FILES)))
DEBUG_DEP_FILES = $(DEBUG_OBJ_FILES:.o=.d)


####################################################################################################
# Release info
#
RELEASE_BUILD_DIR 	= $(BUILD_DIR_PREFIX)/$(RELEASE_DIR_PREFIX)
RELEASE_BINARY 		= $(RELEASE_BUILD_DIR)/$(BINARY_NAME)
RELEASE_OBJ_FILES	= $(addprefix $(RELEASE_BUILD_DIR)/, $(notdir $(OBJ_FILES)))
RELEASE_DEP_FILES 	= $(RELEASE_OBJ_FILES:.o=.d)


####################################################################################################
# Rules
#
.PHONY: all clean debug prep release remake
all: prep debug


####################################################################################################
# Debug rule
#
debug: $(DEBUG_BINARY)

# Compile binary
$(DEBUG_BINARY): $(DEBUG_OBJ_FILES)
	$(CXX) $(CFLAGS) $(DEBUG_CFLAGS) -o $(DEBUG_BINARY) $^

# Compile object files
$(DEBUG_BUILD_DIR)/%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(DEBUG_CFLAGS) -o $@ $<

# Create header dependencies
-include $(DEBUG_DEP_FILES)
$(DEBUG_BUILD_DIR)/%.d: %.cpp
	@$(CXX) $(CFLAGS) $(DEBUG_CFLAGS) $< -MM -MT $(@:.d=.o) >$@


####################################################################################################
# Release rule
#
release: $(RELEASE_BINARY)

# Compile binary
$(RELEASE_BINARY): $(RELEASE_OBJ_FILES)
	$(CXX) $(CFLAGS) $(RELEASE_CFLAGS) -o $(RELEASE_BINARY) $^

#compile object files
$(RELEASE_BUILD_DIR)/%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(RELEASE_CFLAGS) -o $@ $<

# Create header dependencies
-include $(RELEASE_DEP_FILES)
$(RELEASE_BUILD_DIR)/%.d: %.cpp
	@$(CXX) $(CFLAGS) $(RELEASE_CFLAGS) $< -MM -MT $(@:.d=.o) >$@


####################################################################################################
# Other rules
#
prep:
	@mkdir -p $(DEBUG_BUILD_DIR) $(RELEASE_BUILD_DIR)

remake: clean all

clean:
	rm -f $(RELEASE_BINARY) $(RELEASE_OBJ_FILES) $(RELEASE_DEP_FILES) $(DEBUG_BINARY) $(DEBUG_OBJ_FILES) $(DEBUG_DEP_FILES)
