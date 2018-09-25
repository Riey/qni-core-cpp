find_package(Protobuf REQUIRED)

file(GLOB ProtoFiles "protos/*.proto")
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})
add_library(qni.api STATIC ${ProtoSources} ${ProtoHeaders})
