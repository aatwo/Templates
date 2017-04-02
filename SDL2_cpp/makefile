
####################################################################################################
# General info
#
BINARY_NAME 	= MyApp
CFLAGS 			= -I.
LIBS 			= -lSDL2 -lSDL2_image
BUILD_PREFIX	= build
SRC_DIRS		= 	. \
					Logger


####################################################################################################
# Files (auto generated from SRC_DIRS)
#
VPATH			= $(SRC_DIRS) # VPATH is a special make variable allowing any 'current dir' operations to also work on the dirs listed in VPATH (literal magic)
SRC_FILES 		= $(foreach SRC_DIR, $(SRC_DIRS), $(wildcard $(SRC_DIR)/*.cpp)) # This crazy line iterates SRC_DIRS and extracts all the cpp files from each dir
OBJ_FILES 		= $(SRC_FILES:.cpp=.o)


####################################################################################################
# Debug info
#
DEBUG_BUILD_DIR = $(BUILD_PREFIX)/debug
DEBUG_BINARY	= $(DEBUG_BUILD_DIR)/$(BINARY_NAME)
DEBUG_CFLAGS	= -DDEBUG -g
DEBUG_OBJ_FILES = $(addprefix $(DEBUG_BUILD_DIR)/, $(notdir $(OBJ_FILES)))
DEBUG_DEP_FILES = $(DEBUG_OBJ_FILES:.o=.d)


####################################################################################################
# Release info
#
RELEASE_BUILD_DIR 	= $(BUILD_PREFIX)/release
RELEASE_BINARY 		= $(RELEASE_BUILD_DIR)/$(BINARY_NAME)
RELEASE_CFLAGS		= -O3 -DNDEBUG
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
