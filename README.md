# DirectX11-Resource-Handler
This is a header only class that uses std::unique_ptr and move semantics to handle DirectX11 resources

NOTE: The file includes <d3d11> to avoid include ordering where the file would otherwise always need <d3d11> to be included before it's own include to compile
