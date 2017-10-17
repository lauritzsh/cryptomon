exports.fetch = () =>
  fetch('https://api.fixer.io/latest?base=USD')
    .then(res => res.json())
    .then(({ rates }) => [
      { id: 'USD', usd_rate: 1.0 },
      ...Object.keys(rates).map(id => ({ id, usd_rate: rates[id] })),
    ]);
