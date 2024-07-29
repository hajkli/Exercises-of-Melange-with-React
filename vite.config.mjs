import { resolve } from 'path'
import { defineConfig } from 'vite'
import { nodeResolve } from '@rollup/plugin-node-resolve'

export default defineConfig({
  plugins: [nodeResolve()],
  server: {
    watch: {
      ignored: ['**/_opam']
    }
  },
  build: {
    rollupOptions: {
      input: {
        order_confirmation: resolve(__dirname, 'src/order-confirmation/index.html'),
        hello_world: resolve(__dirname, 'src/hello-world/index.html'),
        counter: resolve(__dirname, 'src/counter/index.html'),
        celsius_converter: resolve(__dirname, 'src/celsius-converter/index.html'),
        simple_weather_app: resolve(__dirname, 'src/simple-weather-app/index.html'),
        better_weather_app: resolve(__dirname, 'src/better-weather-app/index.html'),
        basic: resolve(__dirname, 'index.html'),
      }
    }
  }

});
