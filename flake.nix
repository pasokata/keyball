{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            qmk
          ];
          shellHook = ''
            export QMK_HOME="~/keyball/__qmk__"
            ln -s qmk_firmware/keyboards/keyball __qmk__/keyboards/keyball
          '';
        };
      }
    );
}
