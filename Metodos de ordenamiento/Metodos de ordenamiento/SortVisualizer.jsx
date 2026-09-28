import React, { useState, useEffect, useRef } from 'react';
import { Play, Pause, RotateCcw, ChevronDown, Plus, Shuffle } from 'lucide-react';

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
  const [inputMode, setInputMode] = useState('predefined'); // 'predefined' or 'manual'
  const [manualInput, setManualInput] = useState('');
  const [selectedPreset, setSelectedPreset] = useState('random50');
  const stopRef = useRef(false);

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
      // Intercambiar algunos elementos
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
    }
  }, [selectedPreset, inputMode]);

  const handleManualInput = () => {
    try {
      // Parsear la entrada del usuario
      const values = manualInput
        .split(',')
        .map(v => v.trim())
        .filter(v => v !== '')
        .map(v => {
          const num = parseFloat(v);
          if (isNaN(num)) throw new Error(`"${v}" no es un número válido`);
          return Math.abs(num); // Usar valores absolutos para evitar negativos
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
    await sleep(101 - speed);
    return true;
  };

  // Bubble Sort
  const bubbleSort = async (arr) => {
    setCurrentCode('#include <iostream>\n#include <vector>\nusing namespace std;\n\nvoid bubbleSort(vector<int>& arr) {');
    setPseudoCode('🚀 Inicio: Importando librerías necesarias\n📝 Declarando función bubbleSort');
    await sleep(500);

    const n = arr.length;
    setCurrentCode(prev => prev + '\n    int n = arr.size();');
    setPseudoCode('📊 Obteniendo tamaño del arreglo: ' + n);
    await sleep(300);

    for (let i = 0; i < n - 1; i++) {
      setCurrentCode(prev => prev + '\n    for(int i = 0; i < n-1; i++) {');
      setPseudoCode(`🔄 Iteración externa ${i + 1}/${n - 1}\n   Recorriendo el arreglo completo`);
      
      for (let j = 0; j < n - i - 1; j++) {
        if (!await updateVisualization(arr, [j, j + 1])) return;
        
        setPseudoCode(`🔍 Comparando posiciones ${j} y ${j + 1}\n   Valores: ${arr[j]} vs ${arr[j + 1]}`);
        
        const shouldSwap = order === 'asc' ? arr[j] > arr[j + 1] : arr[j] < arr[j + 1];
        
        if (shouldSwap) {
          setCurrentCode(prev => prev + `\n        if(arr[${j}] > arr[${j + 1}]) {`);
          setPseudoCode(`🔀 Intercambiando: ${arr[j]} ↔️ ${arr[j + 1]}\n   Posiciones ${j} y ${j + 1}`);
          
          [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]];
          
          if (!await updateVisualization(arr, [j, j + 1])) return;
          setCurrentCode(prev => prev + '\n            swap(arr[j], arr[j+1]);\n        }');
        }
      }
      setCurrentCode(prev => prev + '\n    }');
      
      // Marcar el último elemento como ordenado
      const sortedIndices = Array.from({ length: i + 1 }, (_, idx) => n - 1 - idx);
      setSorted(sortedIndices);
    }
    
    setCurrentCode(prev => prev + '\n}\n\nint main() {\n    vector<int> arr = {/* datos */};\n    bubbleSort(arr);\n    return 0;\n}');
    setPseudoCode('✅ Ordenamiento completado exitosamente\n🎉 Todos los elementos en su lugar');
    setSorted(arr.map((_, i) => i));
  };

  // Quick Sort
  const quickSort = async (arr, low = 0, high = arr.length - 1, depth = 0) => {
    if (depth === 0) {
      setCurrentCode('#include <iostream>\n#include <vector>\nusing namespace std;\n\nint partition(vector<int>& arr, int low, int high) {');
      setPseudoCode('🚀 Inicio: Quick Sort - Divide y Conquista\n⚡ Algoritmo de ordenamiento rápido');
      await sleep(500);
    }

    if (low < high) {
      setPseudoCode(`🎯 Procesando segmento [${low}...${high}]\n   Tamaño: ${high - low + 1} elementos`);
      const pi = await partition(arr, low, high);
      if (stopRef.current) return;
      
      await quickSort(arr, low, pi - 1, depth + 1);
      if (stopRef.current) return;
      
      await quickSort(arr, pi + 1, high, depth + 1);
    } else if (low === high) {
      setSorted(prev => [...prev, low]);
    }
    
    if (depth === 0) {
      setCurrentCode(prev => prev + '\n}\n\nint main() {\n    vector<int> arr = {/* datos */};\n    quickSort(arr, 0, n-1);\n    return 0;\n}');
      setPseudoCode('✅ Quick Sort completado\n🎉 Arreglo ordenado exitosamente');
      setSorted(arr.map((_, i) => i));
    }
  };

  const partition = async (arr, low, high) => {
    const pivot = arr[high];
    setPseudoCode(`📍 Seleccionando pivote: ${pivot}\n   Posición: ${high}`);
    
    let i = low - 1;
    setCurrentCode(prev => prev + `\n    int pivot = arr[${high}] = ${pivot};`);
    
    for (let j = low; j < high; j++) {
      if (!await updateVisualization(arr, [j, high])) return i + 1;
      
      const shouldMove = order === 'asc' ? arr[j] < pivot : arr[j] > pivot;
      
      if (shouldMove) {
        i++;
        setPseudoCode(`🔀 Moviendo ${arr[j]} antes del pivote\n   Intercambiando posiciones ${i} y ${j}`);
        [arr[i], arr[j]] = [arr[j], arr[i]];
        if (!await updateVisualization(arr, [i, j])) return i + 1;
      }
    }
    
    setPseudoCode(`🎯 Colocando pivote ${pivot} en su posición final\n   Posición: ${i + 1}`);
    [arr[i + 1], arr[high]] = [arr[high], arr[i + 1]];
    if (!await updateVisualization(arr, [i + 1, high])) return i + 1;
    
    setSorted(prev => [...prev, i + 1]);
    return i + 1;
  };

  // Merge Sort
  const mergeSort = async (arr, left = 0, right = arr.length - 1, depth = 0) => {
    if (depth === 0) {
      setCurrentCode('#include <iostream>\n#include <vector>\nusing namespace std;\n\nvoid merge(vector<int>& arr, int l, int m, int r) {');
      setPseudoCode('🚀 Inicio: Merge Sort - Divide y Conquista\n📊 Dividiendo el problema en subproblemas');
      await sleep(500);
    }

    if (left < right) {
      const mid = Math.floor((left + right) / 2);
      setPseudoCode(`✂️ Dividiendo segmento:\n   Izquierda: [${left}...${mid}]\n   Derecha: [${mid + 1}...${right}]`);
      
      await mergeSort(arr, left, mid, depth + 1);
      if (stopRef.current) return;
      
      await mergeSort(arr, mid + 1, right, depth + 1);
      if (stopRef.current) return;
      
      await merge(arr, left, mid, right);
    }
    
    if (depth === 0) {
      setCurrentCode(prev => prev + '\n}\n\nint main() {\n    vector<int> arr = {/* datos */};\n    mergeSort(arr, 0, n-1);\n    return 0;\n}');
      setPseudoCode('✅ Merge Sort completado\n🎉 Todos los segmentos fusionados');
      setSorted(arr.map((_, i) => i));
    }
  };

  const merge = async (arr, left, mid, right) => {
    const leftArr = arr.slice(left, mid + 1);
    const rightArr = arr.slice(mid + 1, right + 1);
    
    setPseudoCode(`🔗 Fusionando subarreglos:\n   Izq: ${leftArr.length} elementos\n   Der: ${rightArr.length} elementos`);
    
    let i = 0, j = 0, k = left;
    
    while (i < leftArr.length && j < rightArr.length) {
      if (stopRef.current) return;
      
      const shouldTakeLeft = order === 'asc' 
        ? leftArr[i] <= rightArr[j] 
        : leftArr[i] >= rightArr[j];
      
      if (shouldTakeLeft) {
        arr[k] = leftArr[i];
        setPseudoCode(`📥 Tomando ${leftArr[i]} del subarreglo izquierdo`);
        i++;
      } else {
        arr[k] = rightArr[j];
        setPseudoCode(`📥 Tomando ${rightArr[j]} del subarreglo derecho`);
        j++;
      }
      
      if (!await updateVisualization(arr, [k])) return;
      k++;
    }
    
    while (i < leftArr.length) {
      arr[k] = leftArr[i];
      if (!await updateVisualization(arr, [k])) return;
      i++;
      k++;
    }
    
    while (j < rightArr.length) {
      arr[k] = rightArr[j];
      if (!await updateVisualization(arr, [k])) return;
      j++;
      k++;
    }
  };

  // Radix Sort
  const radixSort = async (arr) => {
    setCurrentCode('#include <iostream>\n#include <vector>\n#include <algorithm>\nusing namespace std;\n\nvoid radixSort(vector<int>& arr) {');
    setPseudoCode('🚀 Inicio: Radix Sort\n🔢 Ordenamiento por dígitos (LSD)');
    await sleep(500);

    const max = Math.max(...arr);
    setPseudoCode(`📊 Valor máximo encontrado: ${max}\n   Número de dígitos: ${Math.floor(Math.log10(max)) + 1}`);
    
    let digitPosition = 0;
    for (let exp = 1; Math.floor(max / exp) > 0; exp *= 10) {
      if (stopRef.current) return;
      
      setPseudoCode(`🔢 Procesando dígito #${digitPosition + 1}\n   Posición: ${Math.log10(exp).toFixed(0)} (de derecha a izquierda)`);
      setCurrentCode(prev => prev + `\n    // Ordenando por dígito ${digitPosition + 1}`);
      
      await countingSort(arr, exp);
      digitPosition++;
    }
    
    setCurrentCode(prev => prev + '\n}\n\nint main() {\n    vector<int> arr = {/* datos */};\n    radixSort(arr);\n    return 0;\n}');
    setPseudoCode('✅ Radix Sort completado\n🎉 Ordenamiento por dígitos finalizado');
    setSorted(arr.map((_, i) => i));
  };

  const countingSort = async (arr, exp) => {
    const output = new Array(arr.length);
    const count = new Array(10).fill(0);
    
    // Contar ocurrencias
    for (let i = 0; i < arr.length; i++) {
      const digit = Math.floor(arr[i] / exp) % 10;
      count[digit]++;
    }
    
    // Acumular posiciones
    if (order === 'desc') {
      for (let i = 8; i >= 0; i--) {
        count[i] += count[i + 1];
      }
    } else {
      for (let i = 1; i < 10; i++) {
        count[i] += count[i - 1];
      }
    }
    
    // Construir arreglo de salida
    for (let i = arr.length - 1; i >= 0; i--) {
      if (stopRef.current) return;
      
      const digit = Math.floor(arr[i] / exp) % 10;
      output[count[digit] - 1] = arr[i];
      count[digit]--;
    }
    
    // Copiar al arreglo original con visualización
    for (let i = 0; i < arr.length; i++) {
      arr[i] = output[i];
      if (!await updateVisualization(arr, [i])) return;
    }
  };

  const handleSort = async () => {
    if (array.length === 0) {
      alert('Por favor ingresa o selecciona valores primero');
      return;
    }

    stopRef.current = false;
    setSorting(true);
    setSorted([]);
    const arr = [...array];
    
    try {
      switch (algorithm) {
        case 'bubble':
          await bubbleSort(arr);
          break;
        case 'quick':
          await quickSort(arr);
          break;
        case 'merge':
          await mergeSort(arr);
          break;
        case 'radix':
          await radixSort(arr);
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
  };

  const maxValue = array.length > 0 ? Math.max(...array) : 1;
  const shouldShowValues = array.length <= 50; // Mostrar valores solo si hay 50 o menos elementos

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-900 via-purple-900 to-slate-900 text-white p-6">
      <div className="max-w-7xl mx-auto">
        {/* Header */}
        <div className="text-center mb-8">
          <h1 className="text-5xl font-bold mb-2 bg-gradient-to-r from-cyan-400 to-purple-400 bg-clip-text text-transparent">
            Visualizador de Algoritmos de Ordenamiento
          </h1>
          <p className="text-gray-400">Análisis visual y generación de código C++ en tiempo real</p>
        </div>

        {/* Input Mode Selection */}
        <div className="bg-slate-800/50 backdrop-blur-lg rounded-2xl p-6 mb-6 border border-purple-500/30 shadow-2xl">
          <div className="flex gap-4 mb-4">
            <button
              onClick={() => setInputMode('predefined')}
              disabled={sorting}
              className={`flex-1 py-3 px-6 rounded-lg font-medium transition-all border-2 ${
                inputMode === 'predefined'
                  ? 'bg-gradient-to-r from-cyan-500 to-purple-500 border-cyan-400/50 shadow-lg'
                  : 'bg-slate-700/30 border-slate-600 hover:border-purple-400'
              } disabled:opacity-50`}
            >
              📊 Arrays Predefinidos
            </button>
            <button
              onClick={() => setInputMode('manual')}
              disabled={sorting}
              className={`flex-1 py-3 px-6 rounded-lg font-medium transition-all border-2 ${
                inputMode === 'manual'
                  ? 'bg-gradient-to-r from-cyan-500 to-purple-500 border-cyan-400/50 shadow-lg'
                  : 'bg-slate-700/30 border-slate-600 hover:border-purple-400'
              } disabled:opacity-50`}
            >
              ✏️ Entrada Manual
            </button>
          </div>

          {/* Predefined Mode */}
          {inputMode === 'predefined' && (
            <div className="grid grid-cols-2 md:grid-cols-4 gap-3">
              {Object.entries(presets).map(([key, preset]) => (
                <button
                  key={key}
                  onClick={() => setSelectedPreset(key)}
                  disabled={sorting}
                  className={`py-2 px-4 rounded-lg font-medium transition-all border ${
                    selectedPreset === key
                      ? 'bg-purple-600 border-purple-400 shadow-lg'
                      : 'bg-slate-700/50 border-slate-600 hover:border-purple-400'
                  } disabled:opacity-50`}
                >
                  {preset.name}
                </button>
              ))}
            </div>
          )}

          {/* Manual Mode */}
          {inputMode === 'manual' && (
            <div className="space-y-3">
              <div>
                <label className="block text-sm font-medium mb-2 text-cyan-300">
                  Ingresa valores separados por comas (ej: 45, 23, 78, 12, 90)
                </label>
                <div className="flex gap-2">
                  <input
                    type="text"
                    value={manualInput}
                    onChange={(e) => setManualInput(e.target.value)}
                    disabled={sorting}
                    placeholder="45, 23, 78, 12, 90, 156, 34..."
                    className="flex-1 bg-slate-700/50 border border-purple-400/30 rounded-lg px-4 py-3 hover:border-purple-400 transition-all disabled:opacity-50 text-white placeholder-slate-400"
                    onKeyPress={(e) => {
                      if (e.key === 'Enter') handleManualInput();
                    }}
                  />
                  <button
                    onClick={handleManualInput}
                    disabled={sorting}
                    className="bg-gradient-to-r from-cyan-500 to-purple-500 hover:from-cyan-600 hover:to-purple-600 rounded-lg px-6 py-3 font-medium transition-all transform hover:scale-105 disabled:opacity-50 disabled:hover:scale-100 flex items-center gap-2 border border-cyan-400/30 shadow-lg"
                  >
                    <Plus className="w-5 h-5" />
                    Crear Array
                  </button>
                </div>
              </div>
              <div className="text-sm text-gray-400">
                💡 Tip: Puedes ingresar cualquier cantidad de números. Para mejor visualización, usa entre 10-100 valores.
              </div>
            </div>
          )}
        </div>

        {/* Controls */}
        <div className="bg-slate-800/50 backdrop-blur-lg rounded-2xl p-6 mb-6 border border-purple-500/30 shadow-2xl">
          <div className="grid grid-cols-1 md:grid-cols-5 gap-4">
            {/* Algorithm */}
            <div>
              <label className="block text-sm font-medium mb-2 text-cyan-300">Algoritmo</label>
              <div className="relative">
                <select
                  value={algorithm}
                  onChange={(e) => setAlgorithm(e.target.value)}
                  disabled={sorting}
                  className="w-full bg-slate-700/50 border border-purple-400/30 rounded-lg px-4 py-2.5 appearance-none cursor-pointer hover:border-purple-400 transition-all disabled:opacity-50 text-white"
                >
                  {Object.entries(algorithms).map(([key, name]) => (
                    <option key={key} value={key}>{name}</option>
                  ))}
                </select>
                <ChevronDown className="absolute right-3 top-3 w-5 h-5 text-purple-400 pointer-events-none" />
              </div>
            </div>

            {/* Order */}
            <div>
              <label className="block text-sm font-medium mb-2 text-cyan-300">Orden</label>
              <div className="relative">
                <select
                  value={order}
                  onChange={(e) => setOrder(e.target.value)}
                  disabled={sorting}
                  className="w-full bg-slate-700/50 border border-purple-400/30 rounded-lg px-4 py-2.5 appearance-none cursor-pointer hover:border-purple-400 transition-all disabled:opacity-50 text-white"
                >
                  <option value="asc">↑ Menor a Mayor</option>
                  <option value="desc">↓ Mayor a Menor</option>
                </select>
                <ChevronDown className="absolute right-3 top-3 w-5 h-5 text-purple-400 pointer-events-none" />
              </div>
            </div>

            {/* Array Info */}
            <div>
              <label className="block text-sm font-medium mb-2 text-cyan-300">
                Elementos
              </label>
              <div className="bg-slate-700/50 border border-purple-400/30 rounded-lg px-4 py-2.5 text-center">
                <span className="text-2xl font-bold text-purple-400">{array.length}</span>
              </div>
            </div>

            {/* Speed */}
            <div>
              <label className="block text-sm font-medium mb-2 text-cyan-300">
                Velocidad
              </label>
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

            {/* Buttons */}
            <div className="flex gap-2">
              <button
                onClick={sorting ? handleStop : handleSort}
                disabled={array.length === 0}
                className="flex-1 bg-gradient-to-r from-cyan-500 to-purple-500 hover:from-cyan-600 hover:to-purple-600 rounded-lg px-4 py-2.5 font-medium transition-all transform hover:scale-105 disabled:opacity-50 disabled:hover:scale-100 flex items-center justify-center gap-2 border border-cyan-400/30 shadow-lg"
              >
                {sorting ? <Pause className="w-5 h-5" /> : <Play className="w-5 h-5" />}
                {sorting ? 'Pausar' : 'Iniciar'}
              </button>
              <button
                onClick={handleReset}
                disabled={sorting}
                className="bg-slate-700/50 hover:bg-slate-600/50 rounded-lg px-4 py-2.5 transition-all border border-purple-400/30 hover:border-purple-400 disabled:opacity-50"
              >
                <RotateCcw className="w-5 h-5" />
              </button>
            </div>
          </div>
        </div>

        <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
          {/* Visualization */}
          <div className="bg-slate-800/50 backdrop-blur-lg rounded-2xl p-6 border border-purple-500/30 shadow-2xl">
            <h2 className="text-xl font-bold mb-4 text-cyan-300 flex items-center gap-2">
              📊 Visualización
              {array.length > 0 && (
                <span className="text-sm text-gray-400">({array.length} elementos)</span>
              )}
            </h2>
            <div className="h-96 flex items-end justify-center gap-0.5 bg-slate-900/50 rounded-lg p-4 relative">
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
                    className="flex-1 transition-all duration-150 ease-in-out rounded-t relative group"
                    style={{
                      height: `${(value / maxValue) * 100}%`,
                      minWidth: array.length > 100 ? '2px' : array.length > 50 ? '5px' : '10px',
                      backgroundColor: sorted.includes(idx)
                        ? '#10b981'
                        : comparing.includes(idx)
                        ? '#f59e0b'
                        : '#8b5cf6',
                      boxShadow: comparing.includes(idx)
                        ? '0 0 20px rgba(245, 158, 11, 0.6)'
                        : sorted.includes(idx)
                        ? '0 0 20px rgba(16, 185, 129, 0.6)'
                        : 'none'
                    }}
                  >
                    {shouldShowValues && (
                      <div className="absolute -top-6 left-1/2 transform -translate-x-1/2 text-xs font-bold text-white opacity-0 group-hover:opacity-100 transition-opacity bg-slate-800 px-1 py-0.5 rounded whitespace-nowrap">
                        {value}
                      </div>
                    )}
                    {shouldShowValues && array.length <= 30 && (
                      <div className="absolute bottom-1 left-1/2 transform -translate-x-1/2 text-xs font-bold text-white">
                        {value}
                      </div>
                    )}
                  </div>
                ))
              )}
            </div>
            <div className="flex justify-center gap-4 mt-4 text-sm">
              <div className="flex items-center gap-2">
                <div className="w-4 h-4 bg-purple-500 rounded"></div>
                <span className="text-gray-300">Sin ordenar</span>
              </div>
              <div className="flex items-center gap-2">
                <div className="w-4 h-4 bg-amber-500 rounded shadow-lg shadow-amber-500/50"></div>
                <span className="text-gray-300">Comparando</span>
              </div>
              <div className="flex items-center gap-2">
                <div className="w-4 h-4 bg-emerald-500 rounded shadow-lg shadow-emerald-500/50"></div>
                <span className="text-gray-300">Ordenado</span>
              </div>
            </div>
          </div>

          {/* Code & Pseudo */}
          <div className="space-y-6">
            {/* C++ Code */}
            <div className="bg-slate-800/50 backdrop-blur-lg rounded-2xl p-6 border border-purple-500/30 shadow-2xl">
              <h2 className="text-xl font-bold mb-4 text-cyan-300">💻 Código C++</h2>
              <div className="bg-slate-900/80 rounded-lg p-4 h-48 overflow-y-auto font-mono text-sm">
                <pre className="text-green-400 whitespace-pre-wrap">
                  {currentCode || '// El código se generará aquí durante la ejecución...\n// Presiona "Iniciar" para comenzar'}
                </pre>
              </div>
            </div>

            {/* Pseudocode */}
            <div className="bg-slate-800/50 backdrop-blur-lg rounded-2xl p-6 border border-purple-500/30 shadow-2xl">
              <h2 className="text-xl font-bold mb-4 text-cyan-300">📝 Pseudocódigo Explicativo</h2>
              <div className="bg-slate-900/80 rounded-lg p-4 h-32 overflow-y-auto">
                <p className="text-yellow-300 whitespace-pre-wrap">
                  {pseudoCode || '// Las instrucciones paso a paso aparecerán aquí...\n// Observa cómo funciona el algoritmo'}
                </p>
              </div>
            </div>
          </div>
        </div>

        {/* Info Footer */}
        <div className="mt-6 bg-slate-800/30 backdrop-blur-lg rounded-xl p-4 border border-purple-500/20 text-center text-sm text-gray-400">
          <p>
            💡 <strong>Consejo:</strong> Experimenta con diferentes cantidades y algoritmos para entender su complejidad.
            Radix Sort es ideal para números, mientras que Quick Sort es versátil y eficiente.
          </p>
        </div>
      </div>
    </div>
  );
};

export default SortVisualizer;