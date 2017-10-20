exports.fetch = () =>
  fetch('https://api.fixer.io/latest?base=USD')
    .then(res => res.json())
    .then(({ rates }) => [
      { id: 'USD', usd_rate: 1.0 },
      ...Object.keys(rates).map(id => ({ id, usd_rate: 1 / rates[id] })),
    ])
    .then(rates => rates.sort((a, b) => a.id.localeCompare(b.id)));
