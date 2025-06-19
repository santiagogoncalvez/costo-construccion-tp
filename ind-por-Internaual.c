void indPorInternaual(Indice* indices, int ce)
{
    float antIndice;
    float VInteranual;

    for(int i = 0; i < ce; i++)
    {
        if(indices[i].periodo.a > 2022)
        {
            antIndice = buscarfanterior(indices, indices[i].periodo, indices[i].clasificador);
            VInteranual = ((indices[i].indice / antIndice) - 1) * 100;
            indices[i].varInteranual = VInteranual;
        } else {
            indices[i].varInteranual = 0.0;
        }
    }
}

// TODO: terminar de corregir errores y lógica. Esta función debe buscar el elemento índice igual al actual pero de un año anterior, es decir debe tener el mismo contenido en todos los otros campos exceptuando el campo período.  
float buscarfanterior(Indice *indices, Indice *actIndice)
{

    Indice pIndices = indices;
    fecha antPeriodo = fechaRestarDias(&actIndice->periodo, 365);
    // if(antPeriodo.d>1)
    // {
    //     antPeriodo.d=1;
    // }

    while(fechaComparar(&indices->periodo, &antPeriodo)!=0 || !comparar(indices->clasificador, actIndice->clasificador))
    {
        pIndices++;
    }

    return pIndices->indice;
}
