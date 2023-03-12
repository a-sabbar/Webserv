// const mykey = "682500PcukwQUtq1UDd6XimUfAmBA5HL";
const mykey = "QABkXxBI5iBKBxODc3kDHGNAzbrjnRNt";
const dayTime = "./img/day.svg";
const nightTime = "./img/night.svg";

const getWeather = async(cityKey)  => {
    const base =`http://dataservice.accuweather.com/currentconditions/v1/`;
    const query = `${cityKey}?apikey=${mykey}`

    const response = await fetch(base + query)
    const data = await response.json();
    return data[0];
}

const getCity = async(nameCity)  => {
    const base ="http://dataservice.accuweather.com/locations/v1/cities/search";
    const query = `?apikey=${mykey}&q=${nameCity}`

    const response = await fetch(base + query)
    const data = await response.json();
    return data[0];
}
