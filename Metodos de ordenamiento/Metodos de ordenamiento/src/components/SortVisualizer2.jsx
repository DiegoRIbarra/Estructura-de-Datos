import React, { useState, useEffect, useRef, useCallback } from 'react';
import { Play, Pause, RotateCcw, ChevronDown, Plus, Shuffle, Code, FileText, BarChart3, GitBranch, Volume2, VolumeX, Network } from 'lucide-react';

const SortVisualizer = () => {
  const [array, setArray] = useState([]);
  const [sorting, setSorting] = useState(false);
  const [algorithm, setAlgorithm] = useState('bubble');
  const [order, setOrder] = useState('asc');
  const [speed, setSpeed] = useState(50);
  const [currentCode, setCurrentCode] = useState('');
  const [pseudoCode, setPseudoCode] = useState('');
  const [comparing, setComparing] = useState([]);
  const [sorted, setSorted] = useState([]);
  const [inputMode, setInputMode] = useState('predefined');
  const [manualInput, setManualInput] = useState('');
  const [selectedPreset, setSelectedPreset] = useState('random50');
  const [treeVisualization, setTreeVisualization] = useState([]);
  const [soundEnabled, setSoundEnabled] = useState(true);
  const stopRef = useRef(false);
  const audioContextRef = useRef(null);

  // Inicializar Audio Context
  useEffect(() => {
    if (soundEnabled && !audioContextRef.current) {
      try {
        audioContextRef.current = new (window.AudioContext || window.webkitAudioContext)();
      } catch (e) {
        console.log('Audio context not supported');
      }
    }
  }, [soundEnabled]);

  const playSound = useCallback((frequency = 440, duration = 100) => {
    if (!soundEnabled || !audioContextRef.current) return;
    
    try {
      const oscillator = audioContextRef.current.createOscillator();
      const gainNode = audioContextRef.current.createGain();
      
      oscillator.connect(gainNode);
      gainNode.connect(audioContextRef.current.destination);
      
      oscillator.frequency.setValueAtTime(frequency, audioContextRef.current.currentTime);
      oscillator.type = 'sine';
      
      gainNode.gain.setValueAtTime(0.1, audioContextRef.current.currentTime);
      gainNode.gain.exponentialRampToValueAtTime(0.01, audioContextRef.current.currentTime + duration / 1000);
      
      oscillator.start(audioContextRef.current.currentTime);
      oscillator.stop(audioContextRef.current.currentTime + duration / 1000);
    } catch (e) {
      console.log('Audio playback failed');
    }
  }, [soundEnabled]);

  const algorithms = {
    bubble: 'Bubble Sort',
    quick: 'Quick Sort',
    merge: 'Merge Sort',
    radix: 'Radix Sort'
  };

  const presets = {
    random10: { name: '10 Aleatorios', values: () => generateRandomArray(10) },
    random50: { name: '50 Aleatorios', values: () => generateRandomArray(50) },
    random100: { name: '100 Aleatorios', values: () => generateRandomArray(100) },
    ascending: { name: 'Ascendente (1-20)', values: () => Array.from({ length: 20 }, (_, i) => (i + 1) * 20) },
    descending: { name: 'Descendente (20-1)', values: () => Array.from({ length: 20 }, (_, i) => (20 - i) * 20) },
    nearlysorted: { name: 'Casi Ordenado', values: () => {
      const arr = Array.from({ length: 30 }, (_, i) => (i + 1) * 13);
      for (let i = 0; i < 5; i++) {
        const idx1 = Math.floor(Math.random() * arr.length);
        const idx2 = Math.floor(Math.random() * arr.length);
        [arr[idx1], arr[idx2]] = [arr[idx2], arr[idx1]];
      }
      return arr;
    }},
    fewUnique: { name: 'Pocos Únicos', values: () => {
      const unique = [50, 150, 250, 350];
      return Array.from({ length: 40 }, () => unique[Math.floor(Math.random() * unique.length)]);
    }}
  };

  const generateRandomArray = (size) => {
    const arr = [];
    for (let i = 0; i < size; i++) {
      arr.push(Math.floor(Math.random() * 390) + 10);
    }
    return arr;
  };

  useEffect(() => {
    if (inputMode === 'predefined') {
      const preset = presets[selectedPreset];
      setArray(preset.values());
      setSorted([]);
      setComparing([]);
      setTreeVisualization([]);
    }
  }, [selectedPreset, inputMode]);

  const handleManualInput = () => {
    try {
      const values = manualInput
        .split(',')
        .map(v => v.trim())
        .filter(v => v !== '')
        .map(v => {
          const num = parseFloat(v);
          if (isNaN(num)) throw new Error(`"${v}" no es un número válido`);
          return Math.abs(num);
        });

      if (values.length === 0) {
        alert('Por favor ingresa al menos un número');
        return;
      }

      if (values.length > 500) {
        alert('Por favor ingresa máximo 500 números para mejor rendimiento');
        return;
      }

      setArray(values);
      setSorted([]);
      setComparing([]);
      setCurrentCode('');
      setPseudoCode('');
      setTreeVisualization([]);
    } catch (error) {
      alert(error.message);
    }
  };

  const sleep = (ms) => new Promise(resolve => setTimeout(resolve, ms));

  const updateVisualization = async (arr, comp = [], sort = []) => {
    if (stopRef.current) return false;
    setArray([...arr]);
    setComparing(comp);
    setSorted(sort);
    
    if (comp.length > 0) {
      const avgValue = comp.reduce((sum, idx) => sum + arr[idx], 0) / comp.length;
      const frequency = 200 + (avgValue / Math.max(...arr)) * 600;
      playSound(frequency, 80);
    }
    
    await sleep(101 - speed);
    return true;
  };

  const bubbleSort = async (arr) => {
    setCurrentCode(`#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int>& arr) {`);
    setPseudoCode(`FASE 1: INICIALIZACIÓN DEL ALGORITMO
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Importando librerías estándar de C++
• Definiendo función bubbleSort con parámetro por referencia
• El vector se modifica directamente (in-place sorting)`);
    setTreeVisualization(['┌─ BUBBLE SORT INICIADO']);
    await sleep(800);

    const n = arr.length;
    setCurrentCode(prev => prev + `
    int n = arr.size();`);
    setPseudoCode(`FASE 2: ANÁLISIS DEL DATASET
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Calculando tamaño del arreglo: ${n} elementos
• Complejidad temporal: O(n²) - Cuadrática
• Complejidad espacial: O(1) - Constante
• Algoritmo estable: Mantiene orden relativo`);
    await sleep(600);

    for (let i = 0; i < n - 1; i++) {
      setCurrentCode(prev => prev + `\n    \n    // Pasada ${i + 1}: Los ${i} mayores ya están ordenados\n    for(int i = 0; i < n-1; i++) {`);
      setPseudoCode(`FASE 3.${i + 1}: PASADA EXTERNA ${i + 1}/${n - 1}
══════════════════════════════════════════════════════
▶ OBJETIVO: Llevar el elemento más grande al final
▶ RANGO: Posiciones 0 hasta ${n - i - 2}
▶ ELEMENTOS YA ORDENADOS: ${i} (posiciones ${i > 0 ? n - i + ' a ' + (n - 1) : 'ninguna'})
▶ ESTRATEGIA: Comparaciones adyacentes con burbujeo`);
      setTreeVisualization(prev => [...prev, `├─ PASADA ${i + 1}: Rango [0..${n - i - 2}]`]);
      
      for (let j = 0; j < n - i - 1; j++) {
        if (!await updateVisualization(arr, [j, j + 1])) return;
        
        setPseudoCode(`MICRO-OPERACIÓN ${j + 1}: COMPARACIÓN ADYACENTE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
🔍 ANALIZANDO: arr[${j}] vs arr[${j + 1}]
📊 VALORES: ${arr[j]} ${order === 'asc' ? '>' : '<'} ${arr[j + 1]} ?
⚡ CONDICIÓN: ${order === 'asc' ? 'Ordenamiento ascendente' : 'Ordenamiento descendente'}
🎯 DECISIÓN: ${(order === 'asc' ? arr[j] > arr[j + 1] : arr[j] < arr[j + 1]) ? 'INTERCAMBIAR' : 'MANTENER POSICIÓN'}`);
        
        const shouldSwap = order === 'asc' ? arr[j] > arr[j + 1] : arr[j] < arr[j + 1];
        
        if (shouldSwap) {
          setCurrentCode(prev => prev + `\n        \n        // Intercambio necesario: ${arr[j]} > ${arr[j + 1]}\n        if(arr[${j}] > arr[${j + 1}]) {`);
          setPseudoCode(`⚡ EJECUTANDO INTERCAMBIO
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
🔄 SWAP OPERATION: ${arr[j]} ↔ ${arr[j + 1]}
📍 POSICIONES: [${j}] ↔ [${j + 1}]
💾 ALGORITMO C++: Utilizando función swap() de STL
⚙️ IMPLEMENTACIÓN: Intercambio de 3 pasos optimizado
📈 PROGRESO: Elemento ${arr[j]} avanza hacia su posición final`);
          setTreeVisualization(prev => [...prev, `│   ├─ SWAP: ${arr[j]} ↔ ${arr[j + 1]} [pos: ${j},${j+1}]`]);
          
          [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]];
          
          if (!await updateVisualization(arr, [j, j + 1])) return;
          setCurrentCode(prev => prev + `\n            swap(arr[${j}], arr[${j + 1}]);\n        }`);
        } else {
          setTreeVisualization(prev => [...prev, `│   ├─ NO-SWAP: ${arr[j]} ≤ ${arr[j + 1]} [pos: ${j},${j+1}]`]);
        }
      }
      setCurrentCode(prev => prev + `\n    } // Fin pasada ${i + 1}`);
      
      const sortedIndices = Array.from({ length: i + 1 }, (_, idx) => n - 1 - idx);
      setSorted(sortedIndices);
      
      setPseudoCode(`✅ PASADA ${i + 1} COMPLETADA
══════════════════════════════════════════════════════
🎯 RESULTADO: Elemento más grande colocado en posición ${n - 1 - i}
📊 ELEMENTOS ORDENADOS: ${i + 1}/${n}
🔄 COMPARACIONES REALIZADAS: ${n - i - 1}
⏱️ PROGRESO: ${Math.round(((i + 1) / (n - 1)) * 100)}% completado`);
      
      await sleep(400);
    }
    
    setCurrentCode(prev => prev + `
}

/* ╔═══════════════════════════════════════════════════════════╗
   ║                 ANÁLISIS DE COMPLEJIDAD                  ║
   ╠═══════════════════════════════════════════════════════════╣
   ║ • Complejidad Temporal: O(n²) - Todas las situaciones    ║
   ║ • Complejidad Espacial: O(1) - Algoritmo in-place       ║
   ║ • Comparaciones: ${Math.floor((n * (n - 1)) / 2)} operaciones realizadas        ║
   ║ • Intercambios: Variable según orden inicial             ║
   ║ • Estabilidad: ✓ Algoritmo estable                      ║
   ║ • Adaptabilidad: ✗ No optimizado para datos ordenados   ║
   ╚═══════════════════════════════════════════════════════════╝ */

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "Array original: ";
    for(int x : arr) cout << x << " ";
    cout << endl;
    
    bubbleSort(arr, ${n});
    
    cout << "Array ordenado: ";
    for(int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}`);
    
    setPseudoCode(`🎉 BUBBLE SORT COMPLETADO EXITOSAMENTE
══════════════════════════════════════════════════════
✅ ESTADO: Arreglo completamente ordenado
📊 ESTADÍSTICAS DE EJECUCIÓN:
   • Total de elementos: ${n}
   • Pasadas realizadas: ${n - 1}
   • Comparaciones totales: ${Math.floor((n * (n - 1)) / 2)}
   • Orden aplicado: ${order === 'asc' ? 'Ascendente (menor a mayor)' : 'Descendente (mayor a menor)'}

🧮 ANÁLISIS DE COMPLEJIDAD:
   • Tiempo: O(n²) - Cuadrática en todos los casos
   • Espacio: O(1) - Constante, algoritmo in-place
   • Estabilidad: ✓ Mantiene orden relativo de elementos iguales
   
💡 CARACTERÍSTICAS DESTACADAS:
   • Algoritmo de ordenamiento por intercambio
   • Fácil implementación y comprensión
   • Ideal para conjuntos pequeños de datos
   • Detecta automáticamente elementos en posición final`);
    
    setTreeVisualization(prev => [...prev, '└─ ✅ FINALIZADO: Bubble Sort completado exitosamente']);
    setSorted(arr.map((_, i) => i));
  };

  const handleSort = async () => {
    if (array.length === 0) {
      alert('Por favor ingresa o selecciona valores primero');
      return;
    }

    stopRef.current = false;
    setSorting(true);
    setSorted([]);
    setTreeVisualization([]);
    const arr = [...array];
    
    try {
      switch (algorithm) {
        case 'bubble':
          await bubbleSort(arr);
          break;
        default:
          await bubbleSort(arr);
          break;
      }
    } catch (error) {
      console.error('Error durante el ordenamiento:', error);
    }
    
    setSorting(false);
  };

  const handleStop = () => {
    stopRef.current = true;
    setSorting(false);
  };

  const handleReset = () => {
    stopRef.current = true;
    setSorting(false);
    
    if (inputMode === 'predefined') {
      const preset = presets[selectedPreset];
      setArray(preset.values());
    } else {
      setArray([]);
      setManualInput('');
    }
    
    setSorted([]);
    setComparing([]);
    setCurrentCode('');
    setPseudoCode('');
    setTreeVisualization([]);
  };

  const maxValue = array.length > 0 ? Math.max(...array) : 1;
  const shouldShowValues = array.length <= 50;

  return (
    <div className="min-h-screen bg-black text-white p-4 lg:p-6">
      <div className="max-w-8xl mx-auto">
        <div className="text-center mb-6">
          <h1 className="text-4xl lg:text-6xl font-bold mb-3 gradient-text animate-glow">
            VISUALIZADOR DE ALGORITMOS
          </h1>
          <p className="text-gray-300 text-lg">Análisis visual y generación de código C++ en tiempo real</p>
          
          <div className="flex justify-center mt-4">
            <button
              onClick={() => setSoundEnabled(!soundEnabled)}
              className="glass-morphism rounded-full p-3 hover:bg-white hover:bg-opacity-10 transition-all"
            >
              {soundEnabled ? <Volume2 className="w-5 h-5" /> : <VolumeX className="w-5 h-5" />}
            </button>
          </div>
        </div>

        <div className="glass-morphism rounded-xl p-4 lg:p-6 mb-6">
          <div className="flex gap-3 mb-4">
            <button
              onClick={() => setInputMode('predefined')}
              disabled={sorting}
              className={`flex-1 py-3 px-4 lg:px-6 rounded-lg font-medium transition-all flex items-center justify-center gap-2 ${
                inputMode === 'predefined'
                  ? 'bg-white bg-opacity-20 text-white border-2 border-white border-opacity-30'
                  : 'bg-gray-800 bg-opacity-50 text-gray-300 border-2 border-gray-600 hover:border-gray-400'
              } disabled:opacity-50`}
            >
              <BarChart3 className="w-4 h-4" />
              Arrays Predefinidos
            </button>
            <button
              onClick={() => setInputMode('manual')}
              disabled={sorting}
              className={`flex-1 py-3 px-4 lg:px-6 rounded-lg font-medium transition-all flex items-center justify-center gap-2 ${
                inputMode === 'manual'
                  ? 'bg-white bg-opacity-20 text-white border-2 border-white border-opacity-30'
                  : 'bg-gray-800 bg-opacity-50 text-gray-300 border-2 border-gray-600 hover:border-gray-400'
              } disabled:opacity-50`}
            >
              <Plus className="w-4 h-4" />
              Entrada Manual
            </button>
          </div>

          {inputMode === 'predefined' && (
            <div className="grid grid-cols-2 md:grid-cols-4 gap-3">
              {Object.entries(presets).map(([key, preset]) => (
                <button
                  key={key}
                  onClick={() => setSelectedPreset(key)}
                  disabled={sorting}
                  className={`py-2 px-4 rounded-lg font-medium transition-all border ${
                    selectedPreset === key
                      ? 'bg-white bg-opacity-20 border-white border-opacity-40 text-white'
                      : 'bg-gray-700 bg-opacity-50 border-gray-600 text-gray-300 hover:border-gray-400 hover:text-white'
                  } disabled:opacity-50`}
                >
                  {preset.name}
                </button>
              ))}
            </div>
          )}

          {inputMode === 'manual' && (
            <div className="space-y-3">
              <div>
                <label className="block text-sm font-medium mb-2 text-gray-200">
                  Ingresa valores separados por comas (ej: 45, 23, 78, 12, 90)
                </label>
                <div className="flex gap-2">
                  <input
                    type="text"
                    value={manualInput}
                    onChange={(e) => setManualInput(e.target.value)}
                    disabled={sorting}
                    placeholder="45, 23, 78, 12, 90, 156, 34..."
                    className="flex-1 bg-gray-800 bg-opacity-50 border border-gray-600 rounded-lg px-4 py-3 hover:border-gray-400 transition-all disabled:opacity-50 text-white placeholder-gray-400"
                    onKeyPress={(e) => {
                      if (e.key === 'Enter') handleManualInput();
                    }}
                  />
                  <button
                    onClick={handleManualInput}
                    disabled={sorting}
                    className="bg-white bg-opacity-20 hover:bg-opacity-30 rounded-lg px-6 py-3 font-medium transition-all transform hover:scale-105 disabled:opacity-50 disabled:hover:scale-100 flex items-center gap-2 border border-white border-opacity-20"
                  >
                    <Plus className="w-5 h-5" />
                    Crear Array
                  </button>
                </div>
              </div>
              <div className="text-sm text-gray-400 flex items-center gap-2">
                <FileText className="w-4 h-4" />
                Tip: Puedes ingresar cualquier cantidad de números. Para mejor visualización, usa entre 10-100 valores.
              </div>
            </div>
          )}
        </div>

        <div className="glass-morphism rounded-xl p-4 lg:p-6 mb-6">
          <div className="grid grid-cols-1 md:grid-cols-5 gap-4">
            <div>
              <label className="block text-sm font-medium mb-2 text-gray-200 flex items-center gap-1">
                <Code className="w-4 h-4" />
                Algoritmo
              </label>
              <div className="relative">
                <select
                  value={algorithm}
                  onChange={(e) => setAlgorithm(e.target.value)}
                  disabled={sorting}
                  className="w-full bg-gray-800 bg-opacity-50 border border-gray-600 rounded-lg px-4 py-2.5 appearance-none cursor-pointer hover:border-gray-400 transition-all disabled:opacity-50 text-white"
                >
                  {Object.entries(algorithms).map(([key, name]) => (
                    <option key={key} value={key}>{name}</option>
                  ))}
                </select>
                <ChevronDown className="absolute right-3 top-3 w-5 h-5 text-gray-400 pointer-events-none" />
              </div>
            </div>

            <div>
              <label className="block text-sm font-medium mb-2 text-gray-200">Orden</label>
              <div className="relative">
                <select
                  value={order}
                  onChange={(e) => setOrder(e.target.value)}
                  disabled={sorting}
                  className="w-full bg-gray-800 bg-opacity-50 border border-gray-600 rounded-lg px-4 py-2.5 appearance-none cursor-pointer hover:border-gray-400 transition-all disabled:opacity-50 text-white"
                >
                  <option value="asc">↑ Menor a Mayor</option>
                  <option value="desc">↓ Mayor a Menor</option>
                </select>
                <ChevronDown className="absolute right-3 top-3 w-5 h-5 text-gray-400 pointer-events-none" />
              </div>
            </div>

            <div>
              <label className="block text-sm font-medium mb-2 text-gray-200">Elementos</label>
              <div className="bg-gray-800 bg-opacity-50 border border-gray-600 rounded-lg px-4 py-2.5 text-center">
                <span className="text-2xl font-bold text-white">{array.length}</span>
              </div>
            </div>

            <div>
              <label className="block text-sm font-medium mb-2 text-gray-200">Velocidad</label>
              <input
                type="range"
                value={speed}
                onChange={(e) => setSpeed(parseInt(e.target.value))}
                className="w-full h-10"
                min="1"
                max="100"
                disabled={sorting}
              />
            </div>

            <div className="flex gap-2">
              <button
                onClick={sorting ? handleStop : handleSort}
                disabled={array.length === 0}
                className="flex-1 bg-white bg-opacity-20 hover:bg-opacity-30 rounded-lg px-4 py-2.5 font-medium transition-all transform hover:scale-105 disabled:opacity-50 disabled:hover:scale-100 flex items-center justify-center gap-2 border border-white border-opacity-20"
              >
                {sorting ? <Pause className="w-5 h-5" /> : <Play className="w-5 h-5" />}
                {sorting ? 'Pausar' : 'Iniciar'}
              </button>
              <button
                onClick={handleReset}
                disabled={sorting}
                className="bg-gray-800 bg-opacity-50 hover:bg-opacity-70 rounded-lg px-4 py-2.5 transition-all border border-gray-600 hover:border-gray-400 disabled:opacity-50"
              >
                <RotateCcw className="w-5 h-5" />
              </button>
            </div>
          </div>
        </div>

        <div className="grid grid-cols-1 xl:grid-cols-3 gap-4 lg:gap-6">
          <div className="xl:col-span-2 glass-morphism rounded-xl p-4 lg:p-6">
            <h2 className="text-xl font-bold mb-4 text-white flex items-center gap-2">
              <BarChart3 className="w-5 h-5" />
              Visualización
              {array.length > 0 && (
                <span className="text-sm text-gray-400">({array.length} elementos)</span>
              )}
            </h2>
            <div className="h-80 lg:h-96 flex items-end justify-center gap-0.5 bg-black bg-opacity-30 rounded-lg p-4 relative overflow-hidden">
              {array.length === 0 ? (
                <div className="absolute inset-0 flex items-center justify-center text-gray-500">
                  <div className="text-center">
                    <Shuffle className="w-16 h-16 mx-auto mb-4 opacity-50" />
                    <p className="text-lg">Selecciona o ingresa valores para comenzar</p>
                  </div>
                </div>
              ) : (
                array.map((value, idx) => (
                  <div
                    key={idx}
                    className="transition-all duration-200 ease-in-out rounded-t relative group flex-shrink-0"
                    style={{
                      height: `${Math.max(5, (value / maxValue) * 85)}%`,
                      width: Math.max(2, Math.min(20, Math.floor((100 / array.length) * 8))) + 'px',
                      backgroundColor: sorted.includes(idx)
                        ? '#ffffff'
                        : comparing.includes(idx)
                        ? '#d1d5db'
                        : '#6b7280',
                      boxShadow: comparing.includes(idx)
                        ? '0 0 15px rgba(209, 213, 219, 0.8)'
                        : sorted.includes(idx)
                        ? '0 0 15px rgba(255, 255, 255, 0.6)'
                        : 'none'
                    }}
                  >
                    {shouldShowValues && array.length <= 30 && (
                      <div className="absolute -top-6 left-1/2 transform -translate-x-1/2 text-xs font-bold text-white opacity-0 group-hover:opacity-100 transition-opacity bg-black bg-opacity-70 px-1 py-0.5 rounded whitespace-nowrap">
                        {value}
                      </div>
                    )}
                    {shouldShowValues && array.length <= 20 && (
                      <div className="absolute bottom-1 left-1/2 transform -translate-x-1/2 text-xs font-bold text-black">
                        {value}
                      </div>
                    )}
                  </div>
                ))
              )}
            </div>
            <div className="flex justify-center gap-4 mt-4 text-sm">
              <div className="flex items-center gap-2">
                <div className="w-4 h-4 bg-gray-500 rounded"></div>
                <span className="text-gray-300">Sin ordenar</span>
              </div>
              <div className="flex items-center gap-2">
                <div className="w-4 h-4 bg-gray-300 rounded animate-glow"></div>
                <span className="text-gray-300">Comparando</span>
              </div>
              <div className="flex items-center gap-2">
                <div className="w-4 h-4 bg-white rounded animate-glow"></div>
                <span className="text-gray-300">Ordenado</span>
              </div>
            </div>
          </div>

          <div className="glass-morphism rounded-xl p-4 lg:p-6">
            <h2 className="text-xl font-bold mb-4 text-white flex items-center gap-2">
              <GitBranch className="w-5 h-5" />
              Árbol de Decisiones
            </h2>
            <div className="h-80 lg:h-96 bg-black bg-opacity-30 rounded-lg p-4 overflow-auto">
              {treeVisualization.length === 0 ? (
                <div className="flex items-center justify-center h-full text-gray-500">
                  <div className="text-center">
                    <GitBranch className="w-12 h-12 mx-auto mb-3 opacity-50" />
                    <p className="text-sm">El árbol aparecerá durante la ejecución</p>
                  </div>
                </div>
              ) : (
                <div className="space-y-1 font-mono text-xs">
                  {treeVisualization.map((node, idx) => (
                    <div key={idx} className="text-gray-300">
                      {node}
                    </div>
                  ))}
                </div>
              )}
            </div>
          </div>
        </div>

        <div className="grid grid-cols-1 lg:grid-cols-2 gap-4 lg:gap-6 mt-6">
          <div className="glass-morphism rounded-xl p-4 lg:p-6">
            <h2 className="text-xl font-bold mb-4 text-white flex items-center gap-2">
              <Code className="w-5 h-5" />
              Código C++
            </h2>
            <div className="bg-black bg-opacity-50 rounded-lg p-4 h-48 lg:h-64 overflow-y-auto font-mono text-sm">
              <pre className="text-green-300 whitespace-pre-wrap">
                {currentCode || '// El código se generará aquí durante la ejecución...\\n// Presiona "Iniciar" para comenzar'}
              </pre>
            </div>
          </div>

          <div className="glass-morphism rounded-xl p-4 lg:p-6">
            <h2 className="text-xl font-bold mb-4 text-white flex items-center gap-2">
              <FileText className="w-5 h-5" />
              Pseudocódigo Explicativo
            </h2>
            <div className="bg-black bg-opacity-50 rounded-lg p-4 h-48 lg:h-64 overflow-y-auto">
              <p className="text-gray-300 whitespace-pre-wrap font-mono text-sm">
                {pseudoCode || '// Las instrucciones paso a paso aparecerán aquí...\\n// Observa cómo funciona el algoritmo'}
              </p>
            </div>
          </div>
        </div>

        {/* Mapa Visual Profesional - Estilo Hacking */}
        <div className="mt-6 glass-morphism rounded-xl p-4 lg:p-6">
            <h2 className="text-xl font-bold mb-4 text-white flex items-center gap-2">
              <Network className="w-5 h-5" />
              MAPA DE EJECUCIÓN ALGORÍTMICA
            </h2>
            
            <div className="grid grid-cols-1 lg:grid-cols-3 gap-4">
              {/* Diagrama Visual Mejorado */}
              <div className="bg-black bg-opacity-70 rounded-lg p-4 h-48 lg:h-64 overflow-y-auto">
                <h3 className="text-green-400 font-mono text-sm mb-2 text-center">🌳 ÁRBOL DE DECISIONES 🌳</h3>
                <div className="font-mono text-xs text-green-300 whitespace-pre text-center">
{`┌──────────────────────────────┐
│    🔄 PROCESO BUBBLE SORT    │
├──────────────────────────────┤
│                              │
│     🚀 [INICIO]              │
│          │                   │
│          ▼                   │
│    📋 Pasada #{sorting ? Math.floor(Math.random() * 5) + 1 : 'i'}            │
│          │                   │
│          ▼                   │
│   🔍 Comparar números        │
│     arr[j] vs arr[j+1]       │
│          │                   │
│    ┌─────▼─────┐             │
│    │ ¿Necesita │             │
│    │ cambiar?  │             │
│    └─┬─────────┘             │
│      │                       │
│  ✅ SÍ    ❌ NO             │
│   │          │               │
│   ▼          ▼               │
│ 🔄 INTERCAMBIAR 📍 MANTENER │
│   │          │               │
│   └──────────┘               │
│       │                      │
│       ▼                      │
│  🎯 Elemento en su lugar     │
│                              │
└──────────────────────────────┘`}
                </div>
              </div>

              {/* Información del Sistema */}
              <div className="bg-black bg-opacity-70 rounded-lg p-4 h-48 lg:h-64 overflow-y-auto">
                <h3 className="text-cyan-400 font-mono text-sm mb-2 text-center flex items-center justify-center gap-2">
                  <BarChart3 className="w-4 h-4" />
                  INFORMACIÓN DEL PROCESO
                </h3>
                <div className="space-y-3">
                  
                  {/* Estado Actual */}
                  <div className="bg-blue-900 bg-opacity-50 rounded p-2">
                    <div className="text-cyan-200 text-sm font-bold mb-1 flex items-center gap-2">
                      <Play className="w-3 h-3" />
                      Estado Actual:
                    </div>
                    <div className="text-white text-xs">
                      <div>• Algoritmo: <span className="text-cyan-300">{algorithm === 'bubble' ? 'Bubble Sort (Burbuja)' : algorithm}</span></div>
                      <div>• Total de números: <span className="text-green-300">{array.length}</span></div>
                      <div>• Ya ordenados: <span className="text-yellow-300">{sorted.length}</span></div>
                      <div>• Progreso: <span className="text-purple-300">{Math.round((sorted.length / Math.max(array.length, 1)) * 100)}%</span></div>
                    </div>
                  </div>

                  {/* Cómo Funciona */}
                  <div className="bg-yellow-900 bg-opacity-50 rounded p-2">
                    <div className="text-yellow-200 text-sm font-bold mb-1 flex items-center gap-2">
                      <Code className="w-3 h-3" />
                      ¿Cómo Funciona?
                    </div>
                    <div className="text-white text-xs">
                      <div>• Tiempo: <span className="text-red-300">O(n²) - Lento pero seguro</span></div>
                      <div>• Memoria: <span className="text-green-300">O(1) - Muy eficiente</span></div>
                      <div>• Estable: <span className="text-blue-300">✓ Mantiene orden original</span></div>
                      <div>• Fácil: <span className="text-purple-300">✓ Muy fácil de entender</span></div>
                    </div>
                  </div>
                  
                  {/* Estado del Sistema */}
                  <div className="bg-red-900 bg-opacity-50 rounded p-2">
                    <div className="text-red-200 text-sm font-bold mb-1 flex items-center gap-2">
                      <Network className="w-3 h-3" />
                      Estado del Sistema:
                    </div>
                    <div className="text-white text-xs">
                      <div>• Estado: <span className={sorting ? 'text-green-300' : 'text-gray-300'}>{sorting ? '● Ejecutándose' : '○ Parado'}</span></div>
                      <div>• Comparando: <span className={comparing.length > 0 ? 'text-yellow-300' : 'text-gray-300'}>{comparing.length > 0 ? '● Comparando números' : '○ Sin comparar'}</span></div>
                      <div>• Sonido: <span className="text-blue-300 flex items-center gap-1"><Volume2 className="w-3 h-3" />Activado</span></div>
                      <div>• Velocidad: <span className="text-purple-300">{speed}%</span></div>
                    </div>
                  </div>
                </div>
              </div>

              {/* Pasos del Algoritmo */}
              <div className="bg-black bg-opacity-70 rounded-lg p-4 h-48 lg:h-64 overflow-y-auto">
                <h3 className="text-purple-400 font-mono text-sm mb-2 text-center flex items-center justify-center gap-2">
                  <FileText className="w-4 h-4" />
                  PASOS DEL ALGORITMO
                </h3>
                <div className="space-y-2 text-xs">
                  
                  <div className="bg-purple-900 bg-opacity-50 rounded p-2">
                    <div className="text-purple-200 font-bold mb-1 flex items-center gap-2">
                      <Play className="w-3 h-3" />
                      Paso 1: Comenzar
                    </div>
                    <div className="text-white">Tomar la lista de números desordenados</div>
                  </div>
                  
                  <div className="bg-blue-900 bg-opacity-50 rounded p-2">
                    <div className="text-blue-200 font-bold mb-1 flex items-center gap-2">
                      <RotateCcw className="w-3 h-3" />
                      Paso 2: Recorrer
                    </div>
                    <div className="text-white">Ir por cada número de la lista</div>
                  </div>
                  
                  <div className="bg-yellow-900 bg-opacity-50 rounded p-2">
                    <div className="text-yellow-200 font-bold mb-1 flex items-center gap-2">
                      <BarChart3 className="w-3 h-3" />
                      Paso 3: Comparar
                    </div>
                    <div className="text-white">Comparar cada número con el siguiente</div>
                  </div>
                  
                  <div className="bg-green-900 bg-opacity-50 rounded p-2">
                    <div className="text-green-200 font-bold mb-1 flex items-center gap-2">
                      <Shuffle className="w-3 h-3" />
                      Paso 4: Intercambiar
                    </div>
                    <div className="text-white">Si están mal ordenados, cambiarlos de lugar</div>
                  </div>
                  
                  <div className="bg-red-900 bg-opacity-50 rounded p-2">
                    <div className="text-red-200 font-bold mb-1 flex items-center gap-2">
                      <RotateCcw className="w-3 h-3" />
                      Paso 5: Repetir
                    </div>
                    <div className="text-white">Repetir hasta que todos estén ordenados</div>
                  </div>
                  
                  <div className="bg-gray-700 rounded p-2">
                    <div className="text-gray-200 font-bold mb-1 flex items-center gap-2">
                      <Play className="w-3 h-3" />
                      Resultado Final
                    </div>
                    <div className="text-white">Lista completamente ordenada</div>
                  </div>
                </div>
              </div>
            </div>

            {/* Resumen Fácil de Entender */}
            <div className="mt-4 bg-gradient-to-r from-gray-900 to-black rounded-lg p-3 border-l-4 border-green-400">
              <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-2 text-xs">
                <div className="text-green-400 flex items-center gap-2">
                  <Code className="w-4 h-4" />
                  <span>Visualizador Bubble Sort v2.0</span>
                </div>
                <div className="text-cyan-400 flex items-center gap-2">
                  {sorting ? <Play className="w-4 h-4" /> : <Pause className="w-4 h-4" />}
                  <span>{sorting ? 'Ejecutándose' : 'En pausa'}</span>
                </div>
                <div className="text-yellow-400 flex items-center gap-2">
                  <BarChart3 className="w-4 h-4" />
                  <span>{array.length} números | Complejidad: O(n²)</span>
                </div>
                <div className="text-purple-400 flex items-center gap-2">
                  <Volume2 className="w-4 h-4" />
                  <span>Sonido activado | Modo visual avanzado</span>
                </div>
              </div>
            </div>
          </div>

        <div className="mt-6 glass-morphism rounded-xl p-4 text-center text-sm text-gray-300">
          <p className="flex items-center justify-center gap-2">
            <FileText className="w-4 h-4" />
            <strong>Consejo:</strong> Experimenta con diferentes cantidades y algoritmos para entender su complejidad.
            Radix Sort es ideal para números, mientras que Quick Sort es versátil y eficiente.
          </p>
        </div>
      </div>
    </div>
  );
};

export default SortVisualizer;