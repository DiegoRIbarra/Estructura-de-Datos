import React, { useState, useEffect, useRef, useCallback } from 'react';
import { Play, Pause, RotateCcw, ChevronDown, Plus, Shuffle, Code, FileText, BarChart3, GitBranch, Volume2, VolumeX } from 'lucide-react';

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
  const [treeVisualization, setTreeVisualization] = useState([]);
  const [soundEnabled, setSoundEnabled] = useState(true);
  const stopRef = useRef(false);
  const audioContextRef = useRef(null);

  // Inicializar Audio Context
  useEffect(() => {
    if (soundEnabled && !audioContextRef.current) {
      audioContextRef.current = new (window.AudioContext || window.webkitAudioContext)();
    }
  }, [soundEnabled]);

  const playSound = useCallback((frequency = 440, duration = 100) => {
    if (!soundEnabled || !audioContextRef.current) return;
    
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
    
    // Reproducir sonido cuando hay comparación o intercambio
    if (comp.length > 0) {
      const avgValue = comp.reduce((sum, idx) => sum + arr[idx], 0) / comp.length;
      const frequency = 200 + (avgValue / Math.max(...arr)) * 600;
      playSound(frequency, 80);
    }
    
    await sleep(101 - speed);
    return true;
  };

  const bubbleSort = async (arr) => {
    setCurrentCode('#include <iostream>\n#include <vector>\nusing namespace std;\n\nvoid bubbleSort(vector<int>& arr) {');
    setPseudoCode('INICIO: Importando librerías necesarias\nDeclarando función bubbleSort');
    await sleep(500);

    const n = arr.length;
    setCurrentCode(prev => prev + '\n    int n = arr.size();');
    setPseudoCode('ANÁLISIS: Obteniendo tamaño del arreglo: ' + n);
    await sleep(300);

    for (let i = 0; i < n - 1; i++) {
      setCurrentCode(prev => prev + '\n    for(int i = 0; i < n-1; i++) {');
    setPseudoCode(`ITERACIÓN: Pasada externa ${i + 1}/${n - 1}\nRecorriendo el arreglo completo`);
    setTreeVisualization(prev => [...prev, `Pasada ${i + 1}: Iniciando burbujeo`]);
      
      for (let j = 0; j < n - i - 1; j++) {
        if (!await updateVisualization(arr, [j, j + 1])) return;
        
        setPseudoCode(`COMPARACIÓN: Posiciones ${j} y ${j + 1}\nValores: ${arr[j]} vs ${arr[j + 1]}`);
        
        const shouldSwap = order === 'asc' ? arr[j] > arr[j + 1] : arr[j] < arr[j + 1];
        
        if (shouldSwap) {
          setCurrentCode(prev => prev + `\n        if(arr[${j}] > arr[${j + 1}]) {`);
          setPseudoCode(`INTERCAMBIO: ${arr[j]} ↔ ${arr[j + 1]}\nPosiciones ${j} y ${j + 1}`);
          setTreeVisualization(prev => [...prev, `├─ Intercambio: ${arr[j]} ↔ ${arr[j + 1]}`]);
          
          [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]];
          
          if (!await updateVisualization(arr, [j, j + 1])) return;
          setCurrentCode(prev => prev + '\n            swap(arr[j], arr[j+1]);\n        }');
        }
      }
      setCurrentCode(prev => prev + '\n    }');
      
      const sortedIndices = Array.from({ length: i + 1 }, (_, idx) => n - 1 - idx);
      setSorted(sortedIndices);
    }
    
    setCurrentCode(prev => prev + '\n}\n\nint main() {\n    vector<int> arr = {/* datos */};\n    bubbleSort(arr);\n    return 0;\n}');
    setPseudoCode('COMPLETADO: Ordenamiento exitoso\nTodos los elementos en su lugar');
    setTreeVisualization(prev => [...prev, '└─ FINALIZADO: Bubble Sort completado']);
    setSorted(arr.map((_, i) => i));
  };

  const quickSort = async (arr, low = 0, high = arr.length - 1, depth = 0) => {
    if (depth === 0) {
      setCurrentCode('#include <iostream>\n#include <vector>\nusing namespace std;\n\nint partition(vector<int>& arr, int low, int high) {');
      setPseudoCode('INICIO: Quick Sort - Divide y Conquista\nAlgoritmo de ordenamiento rápido');
      setTreeVisualization(['┌─ QUICK SORT INICIADO']);
      await sleep(500);
    }

    if (low < high) {
      setPseudoCode(`SEGMENTO: Procesando [${low}...${high}]\nTamaño: ${high - low + 1} elementos`);
      setTreeVisualization(prev => [...prev, `${'│  '.repeat(depth)}├─ Segmento [${low}..${high}]`]);
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
    
    for (let i = 0; i < arr.length; i++) {
      const digit = Math.floor(arr[i] / exp) % 10;
      count[digit]++;
    }
    
    if (order === 'desc') {
      for (let i = 8; i >= 0; i--) {
        count[i] += count[i + 1];
      }
    } else {
      for (let i = 1; i < 10; i++) {
        count[i] += count[i - 1];
      }
    }
    
    for (let i = arr.length - 1; i >= 0; i--) {
      if (stopRef.current) return;
      
      const digit = Math.floor(arr[i] / exp) % 10;
      output[count[digit] - 1] = arr[i];
      count[digit]--;
    }
    
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
          
          {/* Control de sonido */}
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
          {/* Visualización Principal */}
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
                      height: `${(value / maxValue) * 90}%`,
                      width: Math.max(2, Math.min(20, (100 / array.length) * 8)) + 'px',
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

          {/* Visualización del Árbol de Decisiones */}
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
                <div className="space-y-2">
                  {treeVisualization.map((node, idx) => (
                    <div key={idx} className="flex items-center gap-2 text-sm">
                      <div className="w-2 h-2 bg-white rounded-full"></div>
                      <span className="text-gray-300">{node}</span>
                    </div>
                  ))}
                </div>
              )}
            </div>
          </div>
        </div>

        {/* Sección de Código */}
        <div className="grid grid-cols-1 lg:grid-cols-2 gap-4 lg:gap-6 mt-6">
          {/* Código C++ */}
          <div className="glass-morphism rounded-xl p-4 lg:p-6">
            <h2 className="text-xl font-bold mb-4 text-white flex items-center gap-2">
              <Code className="w-5 h-5" />
              Código C++
            </h2>
            <div className="bg-black bg-opacity-50 rounded-lg p-4 h-48 lg:h-64 overflow-y-auto font-mono text-sm">
              <pre className="text-green-300 whitespace-pre-wrap">
                {currentCode || '// El código se generará aquí durante la ejecución...\n// Presiona "Iniciar" para comenzar'}
              </pre>
            </div>
          </div>

          {/* Pseudocódigo */}
          <div className="glass-morphism rounded-xl p-4 lg:p-6">
            <h2 className="text-xl font-bold mb-4 text-white flex items-center gap-2">
              <FileText className="w-5 h-5" />
              Pseudocódigo Explicativo
            </h2>
            <div className="bg-black bg-opacity-50 rounded-lg p-4 h-48 lg:h-64 overflow-y-auto">
              <p className="text-gray-300 whitespace-pre-wrap">
                {pseudoCode || '// Las instrucciones paso a paso aparecerán aquí...\n// Observa cómo funciona el algoritmo'}
              </p>
            </div>
          </div>
            <div className="bg-slate-800/50 backdrop-blur-lg rounded-2xl p-6 border border-purple-500/30 shadow-2xl">
              <h2 className="text-xl font-bold mb-4 text-cyan-300">💻 Código C++</h2>
              <div className="bg-slate-900/80 rounded-lg p-4 h-48 overflow-y-auto font-mono text-sm">
                <pre className="text-green-400 whitespace-pre-wrap">
                  {currentCode || '// El código se generará aquí durante la ejecución...\n// Presiona "Iniciar" para comenzar'}
                </pre>
              </div>
            </div>

        </div>

        {/* Footer */}
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
