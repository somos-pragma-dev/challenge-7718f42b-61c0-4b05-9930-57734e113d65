# Creación de un motor de renderizado básico

El objetivo es desarrollar un motor de renderizado básico utilizando OpenGL y C++ moderno. El motor debe ser capaz de renderizar objetos 3D simples con luces y sombras. Los objetos serán proporcionados por un archivo de entrada en formato OBJ. El motor debe manejar la carga de estos objetos, la aplicación de luces y sombras, y la renderización en una ventana OpenGL. Los actores involucrados son el 'cargador de archivos OBJ', el 'gestor de luces y sombras' y el'renderizador OpenGL'. La propiedad operativa clave es la 'velocidad de renderizado', con un umbral de '60 FPS en una escena de prueba con 10 objetos'. La razón de negocio es 'proporcionar una base sólida para futuros desarrollos de motores de renderizado más complejos'.

## Informacion General

| Campo | Valor |
|-------|-------|
| **Tema** | Motor de renderizado básico con OpenGL y C++ moderno |
| **Nivel** | junior-l1 |
| **Tipo** | practical |
| **Tiempo estimado** | 2 semanas |

## Fases del Reto

### Fase 0: Configuración del Proyecto

**Objetivo:** Obtener el proyecto base funcional enviando el Código Base a un asistente de IA, que lo analizará, corregirá errores y generará un ZIP listo para usar.

**Tiempo estimado:** 15-30 minutos

**Instrucciones:**

- Asegúrate de tener instalado para ejecutar el proyecto: Node.js 18+, npm, VS Code o similar.
- Copia todo el contenido del campo **Código Base** de este reto — incluyendo el texto de instrucciones que aparece al inicio.
- Abre un asistente de IA (Claude en claude.ai, ChatGPT o Gemini — se recomienda Claude), pega el contenido copiado en el chat y envíalo.
- El asistente analizará los archivos, corregirá errores y generará un archivo ZIP descargable. Descárgalo y extráelo en la carpeta donde quieras trabajar.
- Ejecuta `npm install && npm run build` (o `npm start`). Si no hay errores, estás listo.

**Entregable:** El proyecto compila/arranca sin errores.

<details>
<summary>Pistas de conocimiento</summary>

- Copia el Código Base completo incluyendo el texto de instrucciones al inicio — esas instrucciones le indican al asistente exactamente qué hacer con los archivos.
- Si el asistente no genera el ZIP automáticamente al terminar el análisis, escríbele: "genera el ZIP ahora".
- Si el proyecto tiene errores al arrancar, comparte el mensaje de error con el mismo asistente para que lo corrija.

</details>

### Fase 1: Carga de objetos 3D

**Objetivo:** Desarrollar un componente que cargue objetos 3D desde un archivo OBJ.

**Tiempo estimado:** 3 días

**Instrucciones:**

- Identificar las propiedades clave de un archivo OBJ y cómo mapearlas a estructuras de datos en C++.
- Implementar un componente que lea un archivo OBJ y almacene sus datos en memoria.
- Verificar que el componente pueda cargar correctamente un archivo OBJ de prueba.

**Entregable:** Componente de carga de objetos 3D funcional.

<details>
<summary>Pistas de conocimiento</summary>

- Explorar la estructura de un archivo OBJ y cómo representar sus datos en C++.
- Considerar cómo manejar errores de lectura de archivo.

</details>

### Fase 2: Aplicación de luces y sombras

**Objetivo:** Desarrollar un componente que aplique luces y sombras a los objetos 3D cargados.

**Tiempo estimado:** 4 días

**Instrucciones:**

- Identificar los tipos de luces y sombras que se pueden aplicar en OpenGL.
- Implementar un componente que aplique luces y sombras a los objetos 3D cargados.
- Verificar que el componente pueda aplicar correctamente luces y sombras a un objeto 3D de prueba.

**Entregable:** Componente de aplicación de luces y sombras funcional.

<details>
<summary>Pistas de conocimiento</summary>

- Explorar los tipos de luces y sombras disponibles en OpenGL y cómo aplicarlas.
- Considerar cómo optimizar el rendimiento al aplicar luces y sombras.

</details>

### Fase 3: Renderización en ventana OpenGL

**Objetivo:** Desarrollar un componente que renderice los objetos 3D con luces y sombras en una ventana OpenGL.

**Tiempo estimado:** 5 días

**Instrucciones:**

- Identificar los pasos necesarios para crear una ventana OpenGL y renderizar en ella.
- Implementar un componente que renderice los objetos 3D con luces y sombras en una ventana OpenGL.
- Verificar que el componente pueda renderizar correctamente una escena de prueba con 10 objetos a 60 FPS.

**Entregable:** Componente de renderización en ventana OpenGL funcional.

<details>
<summary>Pistas de conocimiento</summary>

- Explorar los pasos necesarios para crear una ventana OpenGL y renderizar en ella.
- Considerar cómo optimizar el rendimiento para alcanzar los 60 FPS.

</details>

## Dimensiones Evaluadas

- **queEs**: ¿Qué es un archivo OBJ y cómo se mapean sus propiedades a estructuras de datos en C++?
- **paraQueSirve**: ¿Para qué sirve aplicar luces y sombras a los objetos 3D en un motor de renderizado?
- **comoSeUsa**: ¿Cómo se crea una ventana OpenGL y se renderizan objetos 3D en ella?
- **erroresComunes**: ¿Cuáles son los errores comunes al cargar un archivo OBJ y cómo se pueden manejar?
- **queDecisionesImplica**: ¿Qué decisiones implica optimizar el rendimiento para alcanzar los 60 FPS en una escena de prueba con 10 objetos?

## Criterios de Evaluacion

- Componente de carga de objetos 3D funcional.
- Componente de aplicación de luces y sombras funcional.
- Componente de renderización en ventana OpenGL funcional.
- Renderización de una escena de prueba con 10 objetos a 60 FPS.

## Como trabajar con un asistente de IA

Hay dos caminos, elegi uno:

- **AGENTS.md** (recomendado) — instrucciones nativas del repo. Abri esta carpeta con tu agente local (Claude Code, Cursor, Codex, Copilot, Gemini) y las carga solo. Sabe que archivos faltan y con que comando se verifica, y completa el scaffold escribiendo en disco.
- **PROMPT_MEJORA.md** — para copiar y pegar en un chat (claude.ai, ChatGPT). Devuelve un ZIP con el proyecto. Sirve si no tenes un agente en el IDE.

Ninguno de los dos resuelve las fases del reto: eso es tu trabajo.

## Verificacion

El proyecto esta listo para trabajar cuando este comando corre sin errores:

```bash
el comando de build o arranque canonico del stack elegido
```

---

*Reto generado automaticamente por Challenge Generator - Pragma*
