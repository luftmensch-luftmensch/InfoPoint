{
  description = "Flake template to build `InfoPoint`";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/22.05";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self, nixpkgs, utils, ...
  } @ inputs:
    utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
        config.allowUnfree = true;
      };

      mongo-driver = pkgs.stdenv.mkDerivation rec {
        pname = "mongo-c-driver";
        # version = "1.23.1";
        version = "1.23.4";

        src = pkgs.fetchzip {
          url = "https://github.com/mongodb/${pname}/releases/download/${version}/mongo-c-driver-${version}.tar.gz";
          # sha256 = "sha256-K51NxcEa7giTKoZkejban0lC0GCZNuTooXtOKkpfn98=";
          sha256 = "sha256-mJBaRaX0hphvMdTII79DVn1g2uBmpRlObMiJ673Ijpw=";
        };

        preFixup = ''rm -rf "$(pwd)" '';

        nativeBuildInputs = with pkgs; [cmake pkg-config perl];
        buildInputs = with pkgs; [openssl zlib cyrus_sasl];
        propagatedBuildInputs = with pkgs; [libbson snappy];
        cmakeFlags = ["-DCMAKE_BUILD_TYPE=Release" "-DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF" "-DMONGOC_TEST_USE_CRYPT_SHARED=OFF"];
      };
    in {
      devShells.default = pkgs.mkShell {
        name = "infopoint";

        nativeBuildInputs = with pkgs; [gcc gnumake bear pkg-config];
        buildInputs = [mongo-driver];

        shellHook = ''
          echo -e "\t\t\t\t\t\e[1;34m Useful commands: \e[0m\n"
          echo -e "\e[1;33mDebugging:\e[0m\n"
          echo -e "\t\tUsing valgrind: \e[1;32mvalgrind -v -s --keep-debuginfo=yes --leak-check=full --track-origins=yes --suppressions=valgrind.suppressions <EXECUTABLE> \e[0m"
          echo -e "\t\tUsing gdb:      \e[1;32mgdb -tui <EXECUTABLE> \e[0m"
          echo -e "\e[1;33mCompilation:\e[0m\n"
          echo -e "\t\t(Generate sources) -> \e[1;32m cmake -S . -B build/ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \e[0m"
          echo -e "\t\t(Generate build artifacts) -> \e[1;32m cmake --build build/ \e[0m"
          echo -e "\t\t(Remove build artifacts) -> \e[1;32m cmake --build build/ --target clean\e[0m"

          echo -e "\n\n\e[1;31mReady to cry? c:\e[0m"
        '';
      };
    });
}
