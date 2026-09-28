// App.jsx - Ejemplo de uso del Visualizador de Algoritmos

import React from 'react';
import SortVisualizer from './SortVisualizer';

/**
 * EJEMPLO 1: Uso básico
 * El componente funciona completamente standalone
 */
function App() {
  return (
    <div className="App">
      <SortVisualizer />
    </div>
  );
}

export default App;

/**
 * EJEMPLO 2: Integración en una página existente
 */
// function Dashboard() {
//   return (
//     <div className="min-h-screen bg-gray-100">
//       <nav className="bg-white shadow-lg p-4">
//         <h1>Mi Dashboard</h1>
//       </nav>
      
//       <main className="container mx-auto p-4">
//         <SortVisualizer />
//       </main>
      
//       <footer className="bg-gray-800 text-white p-4 text-center">
//         © 2025 Mi Aplicación
//       </footer>
//     </div>
//   );
// }

/**
 * EJEMPLO 3: Con React Router
 */
// import { BrowserRouter, Routes, Route } from 'react-router-dom';
// 
// function AppWithRoutes() {
//   return (
//     <BrowserRouter>
//       <Routes>
//         <Route path="/" element={<Home />} />
//         <Route path="/visualizer" element={<SortVisualizer />} />
//         <Route path="/about" element={<About />} />
//       </Routes>
//     </BrowserRouter>
//   );
// }

/**
 * NOTAS DE INTEGRACIÓN:
 * 
 * 1. El componente es completamente autocontenido
 * 2. No requiere props externas
 * 3. Maneja todo su estado internamente
 * 4. Tailwind CSS debe estar configurado en el proyecto
 * 5. Requiere lucide-react para los iconos
 * 
 * INSTALACIÓN DE DEPENDENCIAS:
 * npm install lucide-react
 * 
 * CONFIGURACIÓN DE TAILWIND:
 * Ver archivo tailwind.config.js de ejemplo incluido
 */
