import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import vercel from 'vite-plugin-vercel'

// https://vitejs.dev/config/
export default defineConfig(() => {
  return {
    plugins: [react(), vercel()],
    define: {
      'process.env.VITE_TOKEN':JSON.stringify(process.env.VITE_TOKEN),
    }
  }
});
