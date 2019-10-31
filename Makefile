
ifneq ($(USE_RTTI), 1)
	CXXFLAGS += -fno-rtti
endif

CXX = g++
CXX_FLAGS = -std=c++1y -O0 -ggdb -g3 

all: lsm_tree 

# CXXFLAGS += -std=c++1y
# $(info PRINT FLAGS $(CXXFLAGS))
# PLATFORM_CXXFLAGS := $(filter-out -std=c++11,$(PLATFORM_CXXFLAGS))
# $(info PRINT FLAGS $(PLATFORM_CXXFLAGS))
# PLATFORM_CXXFLAGS += -std=c++1y
# $(info PRINT FLAGS $(PLATFORM_CXXFLAGS))
# CFLAGS += -std=c++1y
# $(info PRINT FLAGS $(CFLAGS))


lsm_tree: lsm_tree.cc parameter.cc tree_generator.cc workload_generator.cc
	$(CXX) $(CXX_FLAGS)  $@.cc -o$@ parameter.cc tree_generator.cc workload_generator.cc

clean:
	rm -rf lsm_tree  



