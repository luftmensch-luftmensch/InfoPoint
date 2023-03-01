{
  description = "Flake template to build `InfoPoint`"; 
  
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/22.05";
    utils.url = "github:numtide/flake-utils";
  };
  
  outputs = {
    self,
      nixpkgs,
      utils,
      ...
  } @ inputs:
    utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
        config.allowUnfree = true;
      };
      
      mongo-driver = pkgs.stdenv.mkDerivation rec {
        pname = "mongo-c-driver";
        version = "1.23.1";
        
        src = pkgs.fetchzip {
          url = "https://github.com/mongodb/${pname}/releases/download/${version}/mongo-c-driver-${version}.tar.gz";
          #sha256 = "sha256-TjrkJLV/yTw5xrCtXk60pm3GBnqocY3GaFcZVAvrZyM="; 
          sha256 = "sha256-K51NxcEa7giTKoZkejban0lC0GCZNuTooXtOKkpfn98=";
        };
        
        preFixup = ''rm -rf "$(pwd)" '';
        
        nativeBuildInputs = with pkgs; [cmake pkg-config perl];
        buildInputs = with pkgs; [openssl zlib cyrus_sasl];
        propagatedBuildInputs = with pkgs; [libbson snappy];
        cmakeFlags = ["-DCMAKE_BUILD_TYPE=Release" "-DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF" "-DMONGOC_TEST_USE_CRYPT_SHARED=OFF"];
      };
    in {
      devShells.default = pkgs.mkShell {
        name = "potholes";
        
        nativeBuildInputs = with pkgs; [gcc gnumake bear pkg-config];
        buildInputs = [mongo-driver];
        
        shellHook = ''
                echo "Hello, ready to cry with the LSO project?"
              '';
      };
    });
}