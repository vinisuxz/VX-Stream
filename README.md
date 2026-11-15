# VX Stream — Xbox 360

Primeiro esqueleto do aplicativo VX Stream para Xbox 360 RGH/JTAG, usando XSDK.

## O que esta primeira versão contém
- Aplicativo C17 com alvo `VXStream.xex`.
- Interface inicial escura com destaque azul.
- Menu navegável pelo D-pad.
- Alternância Português/Inglês pelos botões LB/RB.
- Saída pelo botão Back.
- Workflow do GitHub Actions para compilar e publicar o XEX como artefato.

## Ainda não implementado
Esta é a primeira casca visual. Ainda não há catálogo online, imagens remotas, player de vídeo,
decodificação H.264/AAC, nem anúncios. Essas partes exigem integração e testes próprios; o
projeto não deve anunciar streaming funcional até que o player seja integrado e testado no console.

## Compilação
O workflow instala o toolchain XSDK, compila o XSDK, configura este projeto com CMake e gera
`build/VXStream.xex`.

O XSDK gera títulos não assinados para consoles RGH/JTAG; não é destinado a consoles retail
bloqueados. Consulte o guia oficial do XSDK:
https://github.com/xenosworks/xsdk/blob/main/docs/GETTING_STARTED.md

## Controles
- D-pad para cima/baixo: navegar.
- LB/RB: alternar idioma.
- A: reservado para abrir a categoria na próxima etapa.
- Back: sair.
