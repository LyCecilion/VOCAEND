{
  description = "VOCAEND — Pwn challenge for hzlt!Game 2026 CTF";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        name = "vocaend";

        buildInputs = with pkgs; [
          gcc
          gnumake
          clang
          clang-tools
        ];

        shellHook = ''
          echo "🎵 VOCAEND dev shell — even if whole world fades away, I won't stop singing my heart out."
        '';
      };
    };
}
