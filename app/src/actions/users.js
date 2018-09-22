import axios from 'axios';

import { API_BASE } from '../constants/api';

const api = axios.create({
  baseURL: API_BASE,
  timeout: 1000,
});

export function getUsers() {
  return api.get('/users').then(response => response.data);
}
