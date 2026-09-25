# AGENTS.md

Instrucciones para el agente de IA que abra este repositorio (Claude Code, Cursor, Codex, Copilot, Gemini). Se cargan solas: no hay que pegar nada en ningun chat.

## Que es este repositorio

Es el codigo base de un reto de aprendizaje de Pragma: **Creación de un motor de renderizado básico**.

| | |
|---|---|
| Tema | Motor de renderizado básico con OpenGL y C++ moderno |
| Nivel | junior-l1 |
| Chapter | Generico |
| Especialidad | Inferido del contexto |
| Stack | C++20 / OpenGL 4.6 |
| Patron arquitectonico | capas estándar con separación de responsabilidades (carga de modelos, gestión de luces, renderizado) |
| Tiempo estimado | 2 semanas |

## Receta del stack

Esqueleto obligatorio:

- `el manifiesto de dependencias del stack, en la raiz`
- `el punto de entrada del stack`
- `la capa de interfaz (controller, handler o equivalente)`
- `las capas que el patron arquitectonico declarado exija, como directorios reales`

Dependencias:

- GLFW 3.3.8
- Glad 0.1.36
- glm 0.9.9.8
- stb_image n/a
- CMake 3.20

## Tu tarea

Dejar este proyecto en estado **verificable**: que el comando de verificacion corra sin errores. Escribi los archivos en disco, en este repositorio. No generes ZIPs ni archivos adjuntos.

En orden:

1. Corre `el comando de build o arranque canonico del stack elegido` y mira que falla.
2. Completa lo que falte de la lista de abajo: manifiesto de dependencias, punto de entrada, capa de interfaz y las capas del patron declarado.
3. Arregla SOLO los errores que impiden compilar o arrancar.
4. Volve a correr `el comando de build o arranque canonico del stack elegido` hasta que pase.
5. Pará ahí.

## Regla dura: las fases son trabajo del humano

**PROHIBIDO implementar los entregables de las fases.** El valor del reto esta en que la persona los resuelva. Tu trabajo es que tenga un proyecto que arranca; el hueco pedagogico se queda como esta.

No resuelvas nada de esto:

- **Fase 1 — Carga de objetos 3D**: Componente de carga de objetos 3D funcional.
- **Fase 2 — Aplicación de luces y sombras**: Componente de aplicación de luces y sombras funcional.
- **Fase 3 — Renderización en ventana OpenGL**: Componente de renderización en ventana OpenGL funcional.

Distincion operativa:

- **Arreglar** (si): import faltante, tipo que no existe, dependencia sin declarar, error de sintaxis, archivo referenciado que no existe.
- **No tocar** (no): logica de negocio incompleta, validaciones ausentes, secretos hardcodeados, APIs deprecadas que funcionan, concurrencia insegura, patrones mejorables. Eso es lo que la persona tiene que encontrar.

## Lo que falta y tenes que completar

### 1. Referencias colgando (4)

Salieron de un analisis estatico del codigo que SI esta en el repo. Cada una rompe la compilacion:

- [ ] `package.json` — `glm`
      "glm": "^0.9.9.8" en dependencies no es un version spec valido de npm. Usa una version publicada real o un rango semver valido (^x.y.z, ~x.y.z, x.y.z, "*"), no un valor inventado.
- [ ] `package.json` — `cmake@3.20.0`
      cmake declara la version 3.20.0, pero el registry de npm respondio que esa version no existe. Es una version inventada: reemplazala por una version publicada real, o si no se conoce con certeza, usa el mecanismo centralizado del ecosistema (BOM/parent/platform/version catalog) y no declares una version individual.
- [ ] `package.json` — `glfw@3.3.8`
      glfw declara la version 3.3.8, pero el registry de npm respondio que esa version no existe. Es una version inventada: reemplazala por una version publicada real, o si no se conoce con certeza, usa el mecanismo centralizado del ecosistema (BOM/parent/platform/version catalog) y no declares una version individual.
- [ ] `package.json` — `glad@0.1.36`
      glad declara la version 0.1.36, pero el registry de npm respondio que esa version no existe. Es una version inventada: reemplazala por una version publicada real, o si no se conoce con certeza, usa el mecanismo centralizado del ecosistema (BOM/parent/platform/version catalog) y no declares una version individual.

### Presentes (15)

- `package.json`
- `assets/models/test_cube.obj`
- `CMakeLists.txt`
- `README.md`
- `src/main.cpp`
- `src/loader/ObjLoader.hpp`
- `src/loader/ObjLoader.cpp`
- `src/lighting/LightManager.hpp`
- `src/lighting/LightManager.cpp`
- `src/renderer/Renderer.hpp`
- `src/renderer/Renderer.cpp`
- `src/utils/ErrorHandler.hpp`
- `src/utils/ErrorHandler.cpp`
- `shaders/vertex_shader.glsl`
- `shaders/fragment_shader.glsl`

### Capas del patron declarado

Cada una tiene que existir como directorio real con al menos un archivo. Codigo plano en la raiz no satisface el patron.

- `src`
- `src/loader`
- `src/lighting`
- `src/renderer`
- `src/utils`
- `shaders`
- `assets/models`
- `assets/textures`

## Verificacion

```bash
el comando de build o arranque canonico del stack elegido
```

Ese comando pasando es la definicion de "terminado" para vos.

## Convenciones que tenes que respetar

- Un solo ecosistema: no declares librerias de otro lenguaje ni mezcles gestores de paquetes.
- Toda libreria que uses tiene que estar declarada en el manifiesto de dependencias.
- Todo import declarado tiene que usarse; todo tipo usado tiene que existir o venir de una dependencia declarada.
- El patron es **capas estándar con separación de responsabilidades (carga de modelos, gestión de luces, renderizado)**: los contratos (interfaces, puertos) los define la capa interna y los implementa la externa, nunca al revés.
- Los archivos que crees llevan implementacion real, no stubs: sin `TODO`, sin cuerpos vacios, sin `// getters y setters`.

## Contexto del candidato

Sirve para calibrar el nivel del codigo, no para resolver las fases.

- Brecha que el reto ataca: Motor de renderizado basico con OpenGL y C++ moderno

---

*Generado por Challenge Generator — Pragma. `README.md` tiene el enunciado completo del reto para la persona. `PROMPT_MEJORA.md` es la variante para pegar en un chat, si se prefiere ese flujo.*
