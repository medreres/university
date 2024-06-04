class PassangersController < ApplicationController
  before_action :set_passanger, only: %i[ show edit update destroy ]

  # GET /passangers or /passangers.json
  def index
    @passangers = Passanger.all
  end

  # GET /passangers/1 or /passangers/1.json
  def show
  end

  # GET /passangers/new
  def new
    @passanger = Passanger.new
  end

  # GET /passangers/1/edit
  def edit
  end

  # POST /passangers or /passangers.json
  def create
    @passanger = Passanger.new(passanger_params)

    respond_to do |format|
      if @passanger.save
        format.html { redirect_to passanger_url(@passanger), notice: "Passanger was successfully created." }
        format.json { render :show, status: :created, location: @passanger }
      else
        format.html { render :new, status: :unprocessable_entity }
        format.json { render json: @passanger.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /passangers/1 or /passangers/1.json
  def update
    respond_to do |format|
      if @passanger.update(passanger_params)
        format.html { redirect_to passanger_url(@passanger), notice: "Passanger was successfully updated." }
        format.json { render :show, status: :ok, location: @passanger }
      else
        format.html { render :edit, status: :unprocessable_entity }
        format.json { render json: @passanger.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /passangers/1 or /passangers/1.json
  def destroy
    @passanger.destroy

    respond_to do |format|
      format.html { redirect_to passangers_url, notice: "Passanger was successfully destroyed." }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_passanger
      @passanger = Passanger.find(params[:id])
    end

    # Only allow a list of trusted parameters through.
    def passanger_params
      params.require(:passanger).permit(:first_name, :last_name, :items_count, :items_weight)
    end
end
