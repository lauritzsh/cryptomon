exports.fetch = () =>
  fetch('https://api.exchangeratesapi.io/latest?base=USD')
    .then(res => res.json())
    .then(({ rates }) => [
      { id: 'usd', code: 'USD', usd_rate: 1.0 },
      ...Object.keys(rates).map(id => ({
        id: id.toLowerCase(),
        code: id,
        usd_rate: 1 / rates[id],
      })),
    ])
    .then(rates => rates.sort((a, b) => a.id.localeCompare(b.id)));
